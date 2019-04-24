#include <sys/time.h>
#include <unistd.h>
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
using chirp::StreamReply;
using chirp::StreamRequest;
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

  // Process StreamRequests from the client
  // Writes back to streamed StreamReplys
  Status stream(ServerContext* context, const StreamRequest* request,
                ServerWriter<StreamReply>* writer) override;

 private:
  int counter = 0;

  // Used for stream bookkeeping
  const std::string kStreamTimestampKey_ = "-ts"; 

  // Number of Timestamps stored in each bookkeeping entry
  const int kStreamTimestampSize_ = 15; 

  // Loop delay for stream()
  const int kStreamLoopDelay_ = 500000;

  // Parses chirp text to find a hashtag
  // @param message: the body of th echirp
  // @ret: vector of all the tags that this chirp belongs to
  std::vector<std::string> ParseTag(const std::string& message);

  // Sets up all Stream bookkeeping info in store
  // @param hashtag: the hashtag being used
  // @param time_str: the timestamp of the chirp 
  // @param id: the id of the chirp that used the `tag`
  void AddTag(const std::string& hashtag, const std::string& timei_str,
              const std::string& id);

  // Helper method for AddTag(). Enters actual bookkeeping info
  // @param stream_info: pointer to streamentry to be added to
  // @param id: chirp_id
  // @param time_str: serialized timestamp of chirp to be added
  // @param key: store key to update bookkeeping data to
  void AddStreamEntry(StreamEntries* stream_info, const std::string& id,
                      const std::string& time_str, std::string key);  

  // Helper method to stream(). Checks StreamData for timestamps and collects
  // newer chirps with `tag`
  // @param hashtag: the hashtag being used
  // @param time_str: the timestamp to be checked against
  // @ret: vector of chirps with `hashtag` that have been made since last stream
  // request
  std::vector<std::string> GetStreamChirps(const std::string& hashtag,
                                           const std::string& time_str);

  // Helper method to GetStreamChirps(). Checks StreamEntries that are after
  // `time_str`
  // @param entries_str: serialized string of StreamEntries to be checked
  // against
  // @param time_str: serialized string of timestamp chirps must come after
  // @ret: vector of chirps in `entries_str` that were made after `time_str`
  std::vector<std::string> ParseStreamEntries(const std::string& entries_str,
                                              const std::string& time_str);
  
  // Utility method to make serialized Timestamp string for current time
  // @param ts_str: string pointer for the Timestamp to be serialized to
  void MakeTimestamp(std::string* ts_str);
};
