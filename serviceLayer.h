#include <chrono>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>
#include "service.grpc.pb.h"

#include "keyValueStore.h"

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
using chirp::StreamTimeData;
using chirp::Timestamp;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using seconds_t = std::chrono::seconds;  // TODO check on this

class ServiceLayerImpliment {
 public:
  int registeruser(std::string user1, KeyValueMap &store);

  int follow(std::string user1, std::string user2, KeyValueMap &store);

  void setup(KeyValueMap &store);

  int add(KeyValueMap &store);

  int getID(KeyValueMap &store);

  int chirp(std::string user1, std::string chirp, std::string parent,
            KeyValueMap &store);

  std::vector<std::string> read(std::string chirp_id, KeyValueMap &stor);

  std::vector<std::string> monitor(std::string user1, KeyValueMap &store);
  
  //Processes stream requests from the client
  //@param user: the user requesting the stream
  //@param hashtag: the tag the user wants to stream
  //@ret: vector of chirps with those hashtags
  std::vector<std::string> stream(const std::string& user, const std::string& hashtag, KeyValueMap& store);

 private:
  int counter = 0;
  
  const std::string kStreamTimestampKey_ = "-ts"; // Used for stream bookkeeping

  int kStreamTimestampSize_ = 15; // Number of Timestamps stored in each bookkeeping entry

  //Parses chirp text to find a hashtag
  //@param message: the body of the chirp
  //@ret: vector of all the tags that this chirp belongs to
  std::vector<std::string> ParseTag(const std::string& message);

  //Sets up all Stream bookkeeping info in store
  //@param tag: the hashtag being used
  //@param time: the timestamp of the chirp was sent at
  //@param id: the id of the chirp that used the `tag`
  void AddTag(const std::string& tag, const std::string& time, const std::string& id, KeyValueMap& store);
};
