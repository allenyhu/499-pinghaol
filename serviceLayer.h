#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/grpcpp.h>
#include "service.grpc.pb.h"
#include "keyValueStore.h"
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

class ServiceLayerImpliment {
    
public:
    int registeruser(string user1,KeyValueMap &store);
    
    int follow (string user1,string user2,KeyValueMap &store);
    
    void setup(KeyValueMap &store);

	int add(KeyValueMap &store);

	int getID(KeyValueMap &store);

    int chirp(string user1,string chirp,string parent,KeyValueMap &store);
    
    vector<string> read(string chirp_id,KeyValueMap &stor);
    
    vector<string>  monitor(string user1,KeyValueMap &store);

private:
    int counter = 0;
    
    
};


