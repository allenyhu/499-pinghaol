#include "store.h"

// get method to keyvalueStore
std::string KeyValueStoreClient::get(std::string key) {
  ClientContext context;
  GetReply reply;
  std::shared_ptr<ClientReaderWriter<GetRequest, GetReply> > stream(
      stub_->get(&context));

  std::thread writer([stream, key]() {
    GetRequest request;
    request.set_key(key);
    std::vector<GetRequest> requestList;
    requestList.push_back(request);

    stream->Write(request);
    stream->WritesDone();
  });

  while (stream->Read(&reply)) {
    std::cout << "Get message " << reply.value() << endl;
  }
  writer.join();
  Status status = stream->Finish();
  if (status.ok()) {
    return reply.value();
  } else {
    std::cout << "Rpc failed." << std::endl;
    return "";
  }
  return "";
}

// Check if a key already exist
int KeyValueStoreClient::contain(std::string key) {
  ClientContext context;
  ContainRequest request;
  request.set_key(key);
  ContainReply reply;
  Status status = stub_->contain(&context, request, &reply);

  if (status.ok()) {
    return reply.contain();
  } else {
    cout << "fail" << endl;
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return reply.contain();
  }
  return reply.contain();
}

// put method to keyvalueStore
void KeyValueStoreClient::put(std::string& key, std::string& value) {
  ClientContext context;
  PutRequest request;
  request.set_key(key);
  request.set_value(value);
  PutReply reply;

  Status status = stub_->put(&context, request, &reply);

  if (status.ok()) {
    cout << "put success" << endl;
  } else {
    cout << "fail" << endl;
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
  }
}

// delete method to keyvalueStore
void KeyValueStoreClient::deletekey(std::string& key) {
  ClientContext context;

  DeleteRequest request;
  request.set_key(key);

  DeleteReply reply;

  Status status = stub_->deletekey(&context, request, &reply);

  if (status.ok()) {
    cout << "delete success" << endl;
  } else {
    cout << "fail" << endl;
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
  }
}
