#include "serviceServer.cc"

KeyValueStoreClient store(
    grpc::CreateChannel("localhost:50000", grpc::InsecureChannelCredentials()));

void RunServer() {
  std::string server_address("0.0.0.0:50002");
  ServiceLayerImpl service;
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}