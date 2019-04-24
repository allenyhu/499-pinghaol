#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include "keyValue.grpc.pb.h"
#include "service.grpc.pb.h"

using chirp::ChirpReply;
using chirp::ChirpRequest;
using chirp::FollowReply;
using chirp::FollowRequest;
using chirp::MonitorReply;
using chirp::MonitorRequest;
using chirp::ReadReply;
using chirp::ReadRequest;
using chirp::RegisterReply;
using chirp::RegisterRequest;
using chirp::ServiceLayer;
using chirp::StreamReply;
using chirp::StreamRequest;
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using namespace std;

class ServiceLayerClient {
 public:
  ServiceLayerClient(std::shared_ptr<Channel> channel)
      : stub_(ServiceLayer::NewStub(channel)) {}

  // register a user
  void registeruser(std::string user);

  // follow a user
  void follow(std::string user1, std::string user2);

  // post a chirp
  void chirp(std::string username, std::string text, std::string replyID);

  // read a chirp
  void read(int chirpID);

  // Read all chrip from a user
  void monitor(std::string username);

  // Stream all chirps with `hashtag`
  void stream(std::string username, std::string hashtag);

 private:
  std::unique_ptr<ServiceLayer::Stub> stub_;
};
