#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <chrono>
#include <ctime>
#include <list>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>
#include "service.grpc.pb.h"

#include "keyValueStore.h"

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
using seconds_t = std::chrono::seconds; // TODO check on this

class ServiceLayerImpliment {   
 public:
  int registeruser(std::string user1, KeyValueMap &store);
    
  int follow (std::string user1, std::string user2, KeyValueMap &store);
    
  void setup(KeyValueMap &store);
  
  int add(KeyValueMap &store);
  
  int getID(KeyValueMap &store);

  int chirp(std::string user1, std::string chirp, std::string parent, KeyValueMap &store);
    
  std::vector<std::string> read(std::string chirp_id,KeyValueMap &stor);
   
  std::vector<std::string> monitor(std::string user1, KeyValueMap &store);

 private:
  int counter = 0;
};


