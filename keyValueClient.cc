#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/keyValue.grpc.pb.h"
#else
#include "keyValue.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using keyValue::KeyValueStore;
using keyValue::PutRequest;
using keyValue::PutReply;
using keyValue::GetRequest;
using keyValue::GetReply;
using keyValue::DeleteRequest;
using keyValue::DeleteReply;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string Put() {
    PutRequest request;

    // Container for the data we expect from the server.
    PutReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->put(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }
    
std::string Gut() {
    GetRequest request;
    
    // Container for the data we expect from the server.
    GetReply reply;
    
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    
    // The actual RPC.
    Status status = stub_->Put(&context, request, &reply);
    
    // Act upon its status.
    if (status.ok()) {
        return reply.message();
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
        << std::endl;
        return "RPC failed";
    }
}

std::string Delete() {
    deleteRequest request;
    
    // Container for the data we expect from the server.
    deleteReply reply;
    
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    
    // The actual RPC.
    Status status = stub_->Put(&context, request, &reply);
    
    // Act upon its status.
    if (status.ok()) {
        return reply.message();
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
        << std::endl;
        return "RPC failed";
    }
}

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {

  GreeterClient greeter(grpc::CreateChannel(
      "localhost:50000", grpc::InsecureChannelCredentials()));



  return 0;
}
