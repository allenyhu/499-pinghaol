#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/grpcpp.h>
#include "keyValue.grpc.pb.h"

using namespace std;
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using chirp::KeyValueStore;
using chirp::PutRequest;
using chirp::PutReply;
using chirp::GetRequest;
using chirp::GetReply;
using chirp::DeleteRequest;
using chirp::DeleteReply;

class KeyValueStoreClient {
 public:
 KeyValueStoreClient(std::shared_ptr<Channel> channel)
      : stub_(KeyValueStore::NewStub(channel)) {}
    
    std::string get(std::string& key) {
        ClientContext context;
//
//        GetRequest request;
//        request.set_key(key);
        GetReply reply;
        std::shared_ptr<ClientReaderWriter<GetRequest, GetReply> > stream(
                        stub_->get(&context));

        std::thread writer([stream,key]() {
            GetRequest request;
            request.set_key(key);
            std::vector<GetRequest> requestList;
            requestList.push_back(request);

            stream->Write(request);
            stream->WritesDone();
        });

        while (stream->Read(&reply)) {
            std::cout << "Get message " <<reply.value()<<endl;
        }
        writer.join();
        Status status = stream->Finish();
        if (status.ok()) {
            return reply.value();
        }
        else {
            std::cout << "RouteChat rpc failed." << std::endl;
        }
    }


    void put(std::string& key,std::string& value) {
        ClientContext context;
        
        PutRequest request;
        request.set_key(key);
        request.set_value(value);
        PutReply reply;

        Status status = stub_->put(&context, request, &reply);
        
        if (status.ok()) {
            cout<<"put success"<<endl;
        }else {
            cout<<"fail"<<endl;
            std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
        }
    }
    
    
    void deletekey(std::string& key) {
        ClientContext context;
        
        DeleteRequest request;
        request.set_key(key);

        DeleteReply reply;
        
        Status status = stub_->deletekey(&context, request, &reply);
        
        if (status.ok()) {
            cout<<"delete success"<<endl;
        }else {
            cout<<"fail"<<endl;
            std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
        }
    }


 private:
  std::unique_ptr<KeyValueStore::Stub> stub_;
};

int main(int argc, char** argv) {
  KeyValueStoreClient test(grpc::CreateChannel(
      "localhost:50000", grpc::InsecureChannelCredentials()));

    std::string key = "0";
    std::string value = "???";
    test.put(key, value );
    test.get(key);
  return 0;
}
