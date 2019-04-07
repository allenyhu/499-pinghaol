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

class ServiceLayerImpl final : public ServiceLayer::Service {
    
public:

	void setup();

	int add();

    Status registeruser(ServerContext* context, const RegisterRequest* request,RegisterReply* reply)override;
    
    Status follow (ServerContext* context, const FollowRequest* request,FollowReply* reply)override;
    
    Status chirp(ServerContext* context, const ChirpRequest* request,ChirpReply* reply)override;
    
    Status read(ServerContext* context,const ReadRequest* request,ReadReply* reply)override;
    
    Status monitor(ServerContext* context,
            const MonitorRequest* request,ServerWriter<MonitorReply>* writer) override;


private:
    int counter = 0;
};


