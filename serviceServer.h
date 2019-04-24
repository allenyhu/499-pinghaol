#include <sys/time.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <random>
#include <string>
#include <thread>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>

#include "service.grpc.pb.h"
#include "store.h"

using chirp::Chirp;
using chirp::ChirpReply;
using chirp::ChirpRequest;
using chirp::Following;
using chirp::FollowReply;
using chirp::FollowRequest;
using chirp::MonitorReply;
using chirp::MonitorRequest;
using chirp::ReadReply;
using chirp::ReadRequest;
using chirp::RegisterReply;
using chirp::RegisterRequest;
using chirp::Reply;
using chirp::ServiceLayer;
using chirp::StreamData;
using chirp::StreamEntries;
using chirp::StreamTimes;
using chirp::Timestamp;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

class ServiceLayerImpl final : public ServiceLayer::Service {
 public:
  void setup();

  int add();

  int getID();

  Status registeruser(ServerContext* context, const RegisterRequest* request,
                      RegisterReply* reply) override;

  Status follow(ServerContext* context, const FollowRequest* request,
                FollowReply* reply) override;

  Status chirp(ServerContext* context, const ChirpRequest* request,
               ChirpReply* reply) override;

  Status read(ServerContext* context, const ReadRequest* request,
              ReadReply* reply) override;

  Status monitor(ServerContext* context, const MonitorRequest* request,
                 ServerWriter<MonitorReply>* writer) override;

 private:
  int counter = 0;

  const std::string kStreamTimestampKey_ =
      "-ts";  // Used for stream bookkeeping

  const int kStreamTimestampSize_ =
      15;  // Number of Timestamps stored in each bookkeeping entry
  // Parses chirp text to find a hashtag
  // @param message: the body of th echirp
  // @ret: vector of all the tags that this chirp belongs to
  std::vector<std::string> ParseTag(const std::string& message);

  // Sets up all Stream bookkeeping info in store
  // @param hashtag: the hashtag being used
  // @param time: the timestamp of the chirp 
  // @param id: the id of the chirp that used the `tag`
  void AddTag(const std::string& hashtag, const std::string& time,
              const std::string& id);

  // Unitility method to make serialized Timestamp string for current time
  // @param ts_str: string pointer for the Timestamp to be serialized to
  void MakeTimestamp(std::string* ts_str);
};
