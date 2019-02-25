#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <chrono>
#include <string>
#include <thread>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/grpcpp.h>
#include "service.grpc.pb.h"
#include "store.h"
#include <ctime>
#include <queue>
#include <list>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using chirp::ServiceLayer;
using chirp::RegisterRequest;
using chirp::RegisterReply;
using chirp::ChirpRequest;
using chirp::ChirpReply;
using chirp::FollowRequest;
using chirp::FollowReply;
using chirp::ReadRequest;
using chirp::ReadReply;
using chirp::MonitorRequest;
using chirp::MonitorReply;
using chirp::Timestamp;
using chirp::Chirp;
using chirp::Following;
using chirp::Reply;
using namespace std;

using seconds_t = std::chrono::seconds;

KeyValueStoreClient store(grpc::CreateChannel(
"localhost:50000", grpc::InsecureChannelCredentials()));

class ServiceLayerImpl final : public ServiceLayer::Service {

private:
    
    int counter = 0;
    
public:
    
    Status registeruser(ServerContext* context, const RegisterRequest* request,RegisterReply* reply)override
    {
        cout<<"Registering User"<<endl;
        string user = request->username();
        string empty = "";
        store.put( user ,empty);
        return Status::OK;
    }
    
    Status follow (ServerContext* context, const FollowRequest* request,FollowReply* reply)override
    {
        cout<<request->username()<<" is following "<<request->to_follow()<<endl;
        string user1 = "U:"+ request->username();
        string user2 = request->to_follow();
        
        Following follow;
        string curr_follow = store.get(user1);
        follow.ParseFromString(curr_follow);
        
        follow.add_username(user2);
        
        string *output = new string;
        follow.SerializeToString(output);
        store.put(user1, *output);
        
        return Status::OK;
        delete output;
    }
    
    Status chirp(ServerContext* context, const ChirpRequest* request,ChirpReply* reply)override
        {
            Chirp newChirp;
            const auto now = std::chrono::system_clock::now();
            const auto epoch = now.time_since_epoch();
            const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);
            const auto ms = std::chrono::duration_cast<std::chrono::microseconds>(epoch);
            
            string id = to_string(counter);
            string username = request->username();
            
            newChirp.set_username(request->username());
            newChirp.set_text(request->text());
            newChirp.set_parent_id(request->parent_id());
            newChirp.mutable_timestamp()->set_seconds( seconds.count());
            newChirp.mutable_timestamp()->set_useconds( ms.count());
            newChirp.set_id(id);
            
            string *output1 = new string;
            newChirp.SerializeToString(output1);
            
            store.put(id ,*output1);
            
            string curr_chirp = store.get(username);
            curr_chirp += id;
            store.put(username, curr_chirp);
            cout<<"Posting Chirp"<<endl;
            reply->mutable_chirp()->set_id(id);
            
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
            
            delete output1;
            
            counter++;
            return Status::OK;
        }

    
    Status read(ServerContext* context,const ReadRequest* request,ReadReply* reply)
    override {
        cout<<"Reading Chirp"<<endl;
        
        Chirp *readChirp = new Chirp;

        string curr = request->chirp_id();
        
        queue <string> open_set;
        open_set.push(curr);
        
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
        
        return Status::OK;
    }
    
//    message MonitorRequest {
//        string username = 1;
//    }
//
//    message MonitorReply {
//        Chirp chirp = 1;
//    }
//
//    rpc monitor (MonitorRequest) returns (stream MonitorReply) {}
    
    Status monitor(ServerContext* context,
                        const MonitorRequest* request,
                        ServerWriter<MonitorReply>* writer) override {
        
        cout<<"monitoring"<<endl;
        string username = request->username();
        string follow = store.get("U:"+ request->username());
        Following follow_user;
        follow_user.ParseFromString(follow);
        MonitorReply reply;
        
        vector<int> list;
        for (int i = 0; i < follow_user.username_size();i++) {
            string ids = store.get(follow_user.username(i));
            list.push_back(ids.length());
            for(char i: ids){
                string a;
                a.push_back(i);
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
            
        }
        

        while(true){
            for (int i = 0; i < follow_user.username_size();i++) {
                string ids = store.get(follow_user.username(i));
                if(list[i] < ids.length()){
                    for(int j = 0; j<ids.length(); j++){
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

        }
        return Status::OK;
    }



};

void RunServer() {
    std::string server_address("0.0.0.0:50002");
    ServiceLayerImpl service;
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
