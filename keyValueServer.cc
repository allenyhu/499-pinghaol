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
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>
#include "keyValue.grpc.pb.h"
#include <thread>
#include <mutex>

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
using chirp::GetRequest;
using chirp::GetReply;
using chirp::DeleteRequest;
using chirp::DeleteReply;
using namespace std;

std::mutex mtx;           // mutex for critical section

    
// Logic and data behind the server's behavior.
class KeyValueStoreImpl final : public KeyValueStore::Service {
    
    Status put(ServerContext* context, const PutRequest* request,PutReply* reply)override
    {
        
        mtx.lock();
        cout<<"Put Connecting"<<endl;
        cout<<"put request key"<<request->key()<<endl;
        cout<<"put value"<<request->value()<<endl;
        map[request->key()] = request->value();
        mtx.unlock();
        return Status::OK;
        
    }
    
    Status get(ServerContext* context,
                     ServerReaderWriter<GetReply, GetRequest>* stream) override {
                mtx.lock();
        cout<<"Get Connecting"<<endl;
        std::vector<GetRequest> requestList;
        GetRequest request;
        std::vector<GetReply> replyList;
        GetReply reply;
        while (stream->Read(&request)) {
//            cout<<"check request"<<request.key()<<endl;
//            cout<<"Check map Value: "<<map[request.key()]<<endl;
//            cout<<"Check map Value: "<<map["0"]<<endl;
            reply.set_value( map[request.key()]);
            cout<<"Value: "<<reply.value()<<endl;
                stream->Write(reply);
            }
                mtx.unlock();

        return Status::OK;
    };


    Status deletekey(ServerContext* context, const DeleteRequest* request,DeleteReply* reply)override
    {
        mtx.lock();
        //cout<<map[request->key()]<<endl;
        cout<<"Delete Connecting"<<endl;
        map.erase(request->key());
        //cout<<map[request->key()]<<endl;
        mtx.unlock();
        return Status::OK;
    }
    
private:
    unordered_map<string, string> map;
    mutex mtx;
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
