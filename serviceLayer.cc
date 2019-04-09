#include <gtest/gtest.h>
#include "serviceLayer.h"


int ServiceLayerImpliment::registeruser(string user1,KeyValueMap &store)
{
    int contain = store.Contain_map(user1);
    if(contain == 1){
        return 1;
    }else{
        string empty = "";
        store.Put_map(user1 ,empty);
        return 0;
    }
    return 1;
}

void ServiceLayerImpliment::setup(KeyValueMap &store){
    string counter_key = "CHIRP_ID_COUNTER";
    string counter_value = "0";
    string check = store.Get_map(counter_key);
    if(check == ""){
        store.Put_map(counter_key,counter_value);
        counter = 0;
    }else{
        counter = stoi(store.Get_map(counter_key));
    }
}

int ServiceLayerImpliment::add(KeyValueMap &store){
    string counter_key = "CHIRP_ID_COUNTER";
    string counter_value = "0";
    string check = store.Get_map(counter_key);
    if(check == ""){
        store.Put_map(counter_key,counter_value);
        counter = 0;
    }
    counter_value = store.Get_map(counter_key);
    counter = stoi(counter_value);
    counter++;
    counter_value = to_string(counter);
    store.Put_map(counter_key,counter_value);
    return counter;
}

int ServiceLayerImpliment::getID(KeyValueMap &store){
    string counter_key = "CHIRP_ID_COUNTER";
    string counter_value = "0";
    string check = store.Get_map(counter_key);
    if(check == ""){
        store.Put_map(counter_key,counter_value);
        counter = 0;
    }else{
        counter_value = store.Get_map(counter_key);
        counter = stoi(counter_value);
    }
    return counter;
}

int ServiceLayerImpliment::follow (string user1,string user2,KeyValueMap &store)
{
    string user = "U:"+ user1;
    
    int contain1 = store.Contain_map(user1);
    int contain2 = store.Contain_map(user2);

    bool alreadyFollowing = false;
    if(contain1 == 1 && contain2  ==1) {
        Following follow;
        string curr_follow = store.Get_map(user);
        follow.ParseFromString(curr_follow);
        
        for (int i = 0; i < follow.username_size();i++) {
            if(follow.username(i) == user2){
                alreadyFollowing = true;
                return 2;
                break;
            }
        }


        if(!alreadyFollowing){
            follow.add_username(user2);
            string *output = new string;
            follow.SerializeToString(output);
            store.Put_map(user, *output);
            // cout<<"success"<<endl;
            delete output;
            return 1;
        }
    }else{
        return 0;
    }

    return 0;
}

int ServiceLayerImpliment::chirp(string user1,string chirp,string parent,KeyValueMap &store)
    {
        getID(store);
        Chirp newChirp;
        unsigned long long time =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();
        
        string id = to_string(counter);
        string username = user1;
        newChirp.set_username(user1);
        newChirp.set_text(chirp);
        newChirp.set_parent_id(parent);
        newChirp.mutable_timestamp()->set_seconds( time/1000);
        newChirp.mutable_timestamp()->set_useconds( time);
        newChirp.set_id(id);
        
        string *output1 = new string;
        newChirp.SerializeToString(output1);
        
        int contain1 = store.Contain_map(user1);
        int contain2 = store.Contain_map(parent);
        if(parent == ""){
            contain2 = 1;
        }
        if(contain1 == 1 && contain2 == 1){
            store.Put_map(id,*output1);
            string curr_chirp = store.Get_map(username);
            curr_chirp += id;
            
            store.Put_map(username, curr_chirp);
            if(parent != ""){
                if( stoi(parent) <= counter){
                    cout<<"curr id: "<< counter<<endl;
                    Reply children;
                    string parent_id = "R:" + parent;
                    
                    string curr_follow_id = store.Get_map(parent_id);
                    children.ParseFromString(curr_follow_id);
                    children.add_id(id);
                    
                    string *output2 = new string;
                    children.SerializeToString(output2);
                    store.Put_map(parent_id ,*output2);
                    delete output2;
                }
            }
            
            delete output1;
            add(store);
            return stoi(id);
        }else if(contain1 == 0){
            return -1;
        }else if(contain2 == 0){
            return -2;
        }
        return 0;
    }

vector<string> ServiceLayerImpliment::read(string chirp_id, KeyValueMap &store)
{
    std::vector<string> v;
    Chirp *readChirp = new Chirp;
    
    int contain = store.Contain_map(chirp_id);
    if(contain == 1){
        queue <string> open_set;
        open_set.push(chirp_id);
        while(!open_set.empty()){
            int size = open_set.size();
            for(int i = 0; i < size; i++){
                string curr = open_set.front();
                open_set.pop();
                string s = store.Get_map(curr);
                readChirp->ParseFromString(s);
                string children_chrips  = store.Get_map( "R:" + readChirp->id());
                // cout<<"children: "<<children_chrips<<endl;
                Reply children;
                children.ParseFromString(children_chrips);
                for(int i = 0; i < children.id_size(); i++){
                    open_set.push(children.id(i));
                }
                v.push_back(readChirp->text());
            
            }
        }
    }else{
        return v;
    }
    return v;

}


vector<string>  ServiceLayerImpliment::monitor(string user1,KeyValueMap &store)
{
    std::vector<string> v;
    string username = user1;
    string follow = store.Get_map("U:"+ user1);
    Following follow_user;
    follow_user.ParseFromString(follow);
    MonitorReply reply;
    
    vector<int> list;
    cout<<"testing : "<<follow_user.username_size()<<endl;
    for (int i = 0; i < follow_user.username_size();i++) {
        string ids = store.Get_map(follow_user.username(i));
        list.push_back(ids.length());
    }

    while(true){
        for (int i = 0; i < follow_user.username_size();i++) {
            string ids = store.Get_map(follow_user.username(i));
            // cout<<"!!"<<ids<<endl;
                for(int j = 0; j<ids.length(); j++){
                    string a;
                    a.push_back(ids[j]);
                    string str_chrip = store.Get_map(a);
                    Chirp temp_chirp;
                    temp_chirp.ParseFromString(str_chrip);
                    reply.mutable_chirp()->set_username(temp_chirp.username());
                    reply.mutable_chirp()->set_text(temp_chirp.text());
                    reply.mutable_chirp()->set_id(temp_chirp.parent_id());
                    reply.mutable_chirp()->set_parent_id(temp_chirp.parent_id());
                    reply.mutable_chirp()->mutable_timestamp()->set_seconds(temp_chirp.timestamp().seconds());
                    reply.mutable_chirp()->mutable_timestamp()->set_useconds(temp_chirp.timestamp().useconds());
                    v.push_back(reply.mutable_chirp()->text());
                }
        }
        break;
    }
    return v;
}




