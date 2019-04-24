#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "keyValue.grpc.pb.h"
#include "keyValueStore.h"

using chirp::ContainReply;
using chirp::ContainRequest;
using chirp::DeleteReply;
using chirp::DeleteRequest;
using chirp::GetReply;
using chirp::GetRequest;
using chirp::KeyValueStore;
using chirp::PutReply;
using chirp::PutRequest;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using namespace std;

// Logic and data behind the server's behavior.
class KeyValueStoreImpl final : public KeyValueStore::Service {
  Status put(ServerContext* context, const PutRequest* request,
             PutReply* reply) override;

  Status contain(ServerContext* context, const ContainRequest* request,
                 ContainReply* reply) override;

  Status get(ServerContext* context,
             ServerReaderWriter<GetReply, GetRequest>* stream) override;

  Status deletekey(ServerContext* context, const DeleteRequest* request,
                   DeleteReply* reply) override;

 private:
  KeyValueMap map;
};
