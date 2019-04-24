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

class ServiceLayerImpliment {
 public:
  int registeruser(std::string user1, KeyValueMap& store);

  int follow(std::string user1, std::string user2, KeyValueMap& store);

  void setup(KeyValueMap& store);

  int add(KeyValueMap& store);

  int getID(KeyValueMap& store);

  int chirp(std::string user1, std::string chirp, std::string parent,
            KeyValueMap& store);

  std::vector<std::string> read(std::string chirp_id, KeyValueMap& stor);

  std::vector<std::string> monitor(std::string user1, KeyValueMap& store);

  // Processes stream requests from the client
  // @param user: the user requesting the stream
  // @param hashtag: the hashtag the user wants to stream
  // @param time: the serialized string of a timestamp of the last stream
  // request
  // @param store: instance of KeyValueMap
  // @ret: vector of chirps with those hashtags
  std::vector<std::string> stream(const std::string& user,
                                  const std::string& hashtag,
                                  const std::string& time, KeyValueMap& store);

  // Utility method to make serialized Timestamp string for current time
  // @param ts_str: string pointer for the Timestamp to be serialized to
  void MakeTimestamp(std::string* ts_str);

 private:
  int counter = 0;

  const std::string kStreamTimestampKey_ =
      "-ts";  // Used for stream bookkeeping

  const int kStreamTimestampSize_ =
      15;  // Number of Timestamps stored in each bookkeeping entry

  // Parses chirp text to find a hashtag
  // @param message: the body of the chirp
  // @ret: vector of all the tags that this chirp belongs to
  std::vector<std::string> ParseTag(const std::string& message);

  // Sets up all Stream bookkeeping info in store
  // @param hashtag: the hashtag being used
  // @param time_str: the timestamp of the chirp was sent at
  // @param id: the id of the chirp that used the `tag`
  // @param store: instance of KeyValueMap
  void AddTag(const std::string& hashtag, const std::string& time_str,
              const std::string& id, KeyValueMap& store);

  // Helper method to stream(). Checks StreamData for timestamps and collects
  // newer chirps with `tag`
  // @param hashtag: the hashtag being used
  // @param time_str: the timestamp to be checked against
  // @param store: instance of KeyValueMap
  // @ret: vector of chirps with `hashtag` that have been made since last stream
  // request
  std::vector<std::string> GetStreamChirps(const std::string& hashtag,
                                           const std::string& time_str,
                                           KeyValueMap& store);

  // Helper method to GetStreamChirps(). Checks StreamEntries that are after
  // `time_str`
  // @param entries_str: serialized string of StreamEntries to be checked
  // against
  // @param time_str: serialized string of timestamp chirps must come after
  // @param store: instance of KeyValueMap
  // @ret: vector of chirps in `entries_str` that were made after `time_str`
  std::vector<std::string> ParseStreamEntries(const std::string& entries_str,
                                              const std::string& time_str,
                                              KeyValueMap& store);
};
