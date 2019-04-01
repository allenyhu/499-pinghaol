#include <algorithm>
#include <cmath>
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/grpcpp.h>
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map> 
#include "keyValue.grpc.pb.h"
#include "keyValueStore.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using chirp::KeyValueStore;
using chirp::PutRequest;
using chirp::PutReply;
using chirp::ContainRequest;
using chirp::ContainReply;
using chirp::GetRequest;
using chirp::GetReply;
using chirp::DeleteRequest;
using chirp::DeleteReply;
using namespace std;
    
// Logic and data behind the server's behavior.
class KeyValueStoreImpl final : public KeyValueStore::Service {
    
    Status put(ServerContext* context, const PutRequest* request,PutReply* reply)override;
    
    Status contain(ServerContext* context, const ContainRequest* request, ContainReply* reply)override;
    
    Status get(ServerContext* context,
                     ServerReaderWriter<GetReply, GetRequest>* stream) override ;


    Status deletekey(ServerContext* context, const DeleteRequest* request,DeleteReply* reply)override;
    
private:
    KeyValueMap map;
};

