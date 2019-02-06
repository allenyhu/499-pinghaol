#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/grpcpp.h>

#include "keyValue.grpc.pb.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using chirp::KeyValueStore;
using chirp::PutRequest;
using chirp::PutReply;
using chirp::GetRequest;
using chirp::GetReply;
using chirp::DeleteRequest;
using chirp::DeleteReply;
using namespace std;

// Logic and data behind the server's behavior.
class KeyValueStoreImpl final : public KeyValueStore::Service {
    
    unordered_map<string, string> map;
    
    Status put(ServerContext* context, const PutRequest* request,PutReply* reply)override
    {
        cout<<"Put Connecting"<<endl;
        map[request->key()] = request->value();
        return Status::OK;
    }
    
    
//    Status get(ServerContext* context,
//                     ServerReaderWriter<GetRequest, GetReply>* stream) override {
//        cout<<"get Connecting"<<endl;
//        GetRequest request;
//        GetReply reply;
//        while (stream->Read(&request)) {
//                reply.value = map[request->key()];
//                stream->write(reply);
//            }
//        }
//
//        return Status::OK;
//    }
    
    Status deletekey(ServerContext* context, const DeleteRequest* request,DeleteReply* reply)override
    {
        //cout<<map[request->key()]<<endl;
        cout<<"Delete Connecting"<<endl;
        map.erase(request->key());
        //cout<<map[request->key()]<<endl;
        return Status::OK;
    }
    
};

void RunServer() {
  std::string server_address("0.0.0.0:50000");
  KeyValueStoreImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
