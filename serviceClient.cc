#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/grpcpp.h>
#include "service.grpc.pb.h"
#include "keyValue.grpc.pb.h"


using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
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
using namespace std;


class ServiceLayerClient {
    public:
    ServiceLayerClient(std::shared_ptr<Channel> channel)
    : stub_(ServiceLayer::NewStub(channel)) {}
    
    void registeruser(std::string user) {
        ClientContext context;
        
        RegisterRequest request;
        request.set_username(user);
        RegisterReply reply;
        
        Status status = stub_->registeruser(&context, request, &reply);
        
        if (status.ok()) {
            if(reply.contain() == 1){
                cout<<"User already exist"<<endl;
            }else{
                cout<<"Register success"<<endl;
            }
        }else {
            cout<<"fail"<<endl;
            std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
        }
    }
    
    void follow (std::string user1, std::string user2) {
        ClientContext context;
        
        FollowRequest request;
        request.set_username(user1);
        request.set_to_follow(user2);
        FollowReply reply;
        
        Status status = stub_->follow (&context, request, &reply);
        
        if (status.ok()) {
            if(reply.contain() == 1){
                cout<<"Follow success"<<endl;
            }else{
                cout<<"User doesn't esist"<<endl;
            }
        }else {
            cout<<"fail"<<endl;
            std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
        }
    }
    
    void chirp(std::string username, std::string text, std::string replyID) {
        ClientContext context;

        ChirpRequest request;
        request.set_username(username);
        request.set_text(text);
        request.set_parent_id(replyID);
        ChirpReply reply;
        
        Status status = stub_->chirp (&context, request, &reply);
        
        if (status.ok()) {
            if(reply.contain() == 0){
                cout<<"No such user"<<endl;
            }else if(reply.contain() == -1){
                cout<<"No such parent chirp"<<endl;
            }else{
                cout<<"Post success, chirp id for this chirp is: "<<reply.chirp().id()<<endl;
            }
        }else {
            cout<<"fail"<<endl;
            std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
        }
    }
    
    void read (int id) {
        ClientContext context;
        ReadRequest request;
        request.set_chirp_id(to_string(id));
        ReadReply reply;

        Status status = stub_->read (&context, request, &reply);
        if (status.ok()) {
           if(reply.contain() == 0){
               cout<<"No such Chirp"<<endl;}
           else{
                for(int i = 0; i< reply.chirps().size();i++){
                    cout<<"Reading chirps posted by "<<reply.chirps(i).username();
                    cout<<": \n\n";
                    cout<<reply.chirps(i).text()<<endl;
                    cout<<"\n";
                }
           }
        } else {
            std::cout << "Read rpc failed." << std::endl;
        }
    }
    
    void monitor(std::string username) {
        MonitorRequest request;
        ClientContext context;
        MonitorReply reply;
        
        request.set_username(username);
        std::unique_ptr<ClientReader<MonitorReply> > reader(
                                                       stub_->monitor(&context, request));
        std::cout << "Start monitoring "<<endl;
        while (reader->Read(&reply)) {
            cout<< reply.chirp().username()<<": "
            << reply.chirp().text() <<endl;
        }
        Status status = reader->Finish();
        if (status.ok()) {
            std::cout << "ListFeatures rpc succeeded." << std::endl;
        } else {
            std::cout << "ListFeatures rpc failed." << std::endl;
        }
    }


    
private:
    std::unique_ptr<ServiceLayer::Stub> stub_;
};

int main(int argc, char** argv) {
    ServiceLayerClient test(grpc::CreateChannel(
        "localhost:50002", grpc::InsecureChannelCredentials()));
    string array[7];
    string curr;
    cout<<"argc: "<<argc<<endl;
    if(argc<=7){
        for(int i = 0; i<argc ; i++){
            array[i] = argv[i];
        }
        
        if(argc == 3){
            if(array[1] == "--register"){
                test.registeruser(array[2]);
            }else if(array[1] == "--read"){
                test.read(stoi(array[2]));
            }else{
                cout<<"Invalid command-line flags"<<endl;
            }
        }else if(argc == 4){
            if(array[1] == "--user" && array[3] == "--monitor"){
                curr = array[2];
                test.monitor(curr);
            }else{
                cout<<"Invalid command-line flags"<<endl;
            }
        }else if(argc == 5){
            if(array[1] == "--user"){
                curr = array[2];
            }
            if(array[3] == "--chirp"){
                test.chirp(curr,array[4],"");
            }
            else if(array[3] == "--follow"){
                test.follow(curr, array[4]);
            }else{
                cout<<"Invalid command-line flags"<<endl;
            }
        }else if(argc == 7){
                if(array[1] == "--user" && array[3] == "--chirp" && array[5] == "--reply"){
                    curr = array[2];
                    test.chirp(curr,array[4],array[6]);
                }else{
                    cout<<"Invalid command-line flags"<<endl;
                }
            }else{
                cout<<"Invalid command-line flags"<<endl;
            }
    }else{
        cout<<"Too many argument"<<endl;
    }

    return 0;
}
