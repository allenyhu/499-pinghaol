#include "serviceServer.h"

KeyValueStoreClient store(grpc::CreateChannel(
"localhost:50000", grpc::InsecureChannelCredentials()));

Status ServiceLayerImpl::registeruser(ServerContext* context, const RegisterRequest* request,RegisterReply* reply)
{
    std::cout<<"Registering User"<<std::endl;
    int contain = store.contain(request->username());
    if(contain == 1){
        reply->set_contain(1);
    }else{
        reply->set_contain(0);
        string user = request->username();
        string empty = "";
        store.put( user ,empty);
    }
    return Status::OK;
}

void ServiceLayerImpl::setup(){
    string counter_key = "CHIRP_ID_COUNTER";
    string counter_value = "0";
    string check = store.get(counter_key);
    if(check == ""){
        store.put(counter_key,counter_value);
        counter = 0;
    }else{
        counter = stoi(store.get(counter_key));
    }
}

int ServiceLayerImpl::add(){
    string counter_key = "CHIRP_ID_COUNTER";
    string counter_value = "0";
    string check = store.get(counter_key);
    if(check == ""){
        store.put(counter_key,counter_value);
        counter = 0;
    }
    counter_value = store.get(counter_key);
    counter = stoi(counter_value);
    counter++;
    counter_value = to_string(counter);
    store.put(counter_key,counter_value);
    return counter;
}

Status ServiceLayerImpl::follow (ServerContext* context, const FollowRequest* request,FollowReply* reply)
{
    string user1 = "U:"+ request->username();
    string user2 = request->to_follow();
    
    int contain1 = store.contain(request->username());
    int contain2 = store.contain(user2);

    bool alreadyFollowing = false;
    if(contain1 == 1 && contain2  ==1) {
        Following follow;
        string curr_follow = store.get(user1);
        follow.ParseFromString(curr_follow);
        
        for (int i = 0; i < follow.username_size();i++) {
            if(follow.username(i) == user2){
                alreadyFollowing = true;
                reply->set_contain(2);
                cout<<user1<<" already follow "<<user2<<endl;
                break;
            }
        }

        if(!alreadyFollowing){
            follow.add_username(user2);
            reply->set_contain(1);
            string *output = new string;
            follow.SerializeToString(output);
            store.put(user1, *output);
            delete output;
        }
    }else{
        reply->set_contain(0);
    }

    return Status::OK;
}

Status ServiceLayerImpl::chirp(ServerContext* context, const ChirpRequest* request,ChirpReply* reply)
    {
        Chirp newChirp;
        unsigned long long time =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();
        
        string id = to_string(counter);
        string username = request->username();
        
        newChirp.set_username(request->username());
        newChirp.set_text(request->text());
        newChirp.set_parent_id(request->parent_id());
        newChirp.mutable_timestamp()->set_seconds( time/1000);
        newChirp.mutable_timestamp()->set_useconds( time);
        newChirp.set_id(id);
        
        string *output1 = new string;
        newChirp.SerializeToString(output1);
        
        int contain1 = store.contain(request->username());
        int contain2 = store.contain(request->parent_id());
        if(request->parent_id() == ""){
            contain2 = 1;
        }
        if(contain1 == 1 && contain2 == 1){
            reply->set_contain(1);
            store.put(id,*output1);
            string curr_chirp = store.get(username);
            curr_chirp += id;
            
            store.put(username, curr_chirp);
            cout<<"Posting Chirp"<<endl;
            reply->mutable_chirp()->set_id(id);
            if(request->parent_id() != ""){
                if( stoi(request->parent_id()) <= counter){
                    Reply children;
                    string parent_id = "R:" + request->parent_id();
                    
                    string curr_follow_id = store.get(parent_id);
                    children.ParseFromString(curr_follow_id);
                    children.add_id(id);
                    
                    string *output2 = new string;
                    children.SerializeToString(output2);
                    store.put(parent_id ,*output2);
                    delete output2;
                }
            }
            
            delete output1;
            add();
        }else if(contain1 == 0){
            reply->set_contain(0);
        }else if(contain2 == 0){
            reply->set_contain(-1);
        }

        return Status::OK;
    }


Status ServiceLayerImpl::read(ServerContext* context,const ReadRequest* request,ReadReply* reply)
{
    cout<<"Reading Chirp"<<endl;
    Chirp *readChirp = new Chirp;
    
    int contain = store.contain(request->chirp_id());
    if(contain == 1){
        string curr = request->chirp_id();
        queue <string> open_set;
        open_set.push(curr);
        reply->set_contain(1);
        while(!open_set.empty()){
            int size = open_set.size();
            for(int i = 0; i < size; i++){
                string curr = open_set.front();
                open_set.pop();
                string s = store.get(curr);
                readChirp = reply->add_chirps();
                readChirp->ParseFromString(s);
                
                string children_chrips  = store.get( "R:" + readChirp->id());
                
                Reply children;
                children.ParseFromString(children_chrips);
                for(int i = 0; i < children.id_size(); i++){
                    open_set.push(children.id(i));
                }
            
            }
        }
    }else{
        reply->set_contain(0);
    }
    return Status::OK;
}


Status ServiceLayerImpl::monitor(ServerContext* context,
    const MonitorRequest* request,ServerWriter<MonitorReply>* writer){
    
    cout<<"monitoring"<<endl;
    string username = request->username();
    string follow = store.get("U:"+ request->username());
    Following follow_user;
    follow_user.ParseFromString(follow);
    MonitorReply reply;
    
    vector<int> list;
    //cout<<"testing : "<<follow_user.username_size()<<endl;
    for (int i = 0; i < follow_user.username_size();i++) {
        string ids = store.get(follow_user.username(i));
        list.push_back(ids.length());
    }

    while(true){
        for (int i = 0; i < follow_user.username_size();i++) {
            string ids = store.get(follow_user.username(i));
            if(list[i] < ids.length()){
                for(int j = list[i]; j<ids.length(); j++){
                    string a;
                    a.push_back(ids[j]);
                    string str_chrip = store.get(a);
                    Chirp temp_chirp;
                    temp_chirp.ParseFromString(str_chrip);
                    reply.mutable_chirp()->set_username(temp_chirp.username());
                    reply.mutable_chirp()->set_text(temp_chirp.text());
                    reply.mutable_chirp()->set_id(temp_chirp.parent_id());
                    reply.mutable_chirp()->set_parent_id(temp_chirp.parent_id());
                    reply.mutable_chirp()->mutable_timestamp()->set_seconds(temp_chirp.timestamp().seconds());
                    reply.mutable_chirp()->mutable_timestamp()->set_useconds(temp_chirp.timestamp().useconds());
                    writer->Write(reply);
                }
                list[i] = ids.length();
            }

            if (context->IsCancelled()) {
                break;
            }
        }
        if (context->IsCancelled()) {
            break;
        }
    }
    return Status::OK;
}


void RunServer() {
    std::string server_address("0.0.0.0:50002");

    ServiceLayerImpl service;
    service.setup();
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
