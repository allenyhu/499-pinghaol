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
    
    //register a user
    void registeruser(std::string user);
    
    //follow a user
    void follow (std::string user1, std::string user2);
    
    //post a chirp
    void chirp(std::string username, std::string text, std::string replyID) ;

    //read a chirp
    void read (int chirpID) ;
    
    //Read all chrip from a user
    void monitor(std::string username);


    
private:
    std::unique_ptr<ServiceLayer::Stub> stub_;
};