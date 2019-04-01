#include "keyValueServer.h"


    
    Status KeyValueStoreImpl::put(ServerContext* context, const PutRequest* request,PutReply* reply)
    {
        // cout<<"Put Connecting"<<endl;
        // cout<<" put key: "<<request->key()<<endl;
        // cout<<" put value: "<<request->value()<<endl;

        map.Put_map(request->key(),request->value());
        return Status::OK;
        
    }
    
    Status KeyValueStoreImpl::contain(ServerContext* context, const ContainRequest* request, ContainReply* reply)
    {

        cout<<"Contain Connecting"<<endl;
        if (map.Contain_map(request->key()))
        {
            reply->set_contain(0);
            cout<<"key doesn't exist"<<endl;
        }else{
            reply->set_contain(1);
        }
        
        return Status::OK;

    }
    
    Status KeyValueStoreImpl::get(ServerContext* context,
                     ServerReaderWriter<GetReply, GetRequest>* stream)  {
        // cout<<"Get Connecting"<<endl;
        std::vector<GetRequest> requestList;
        GetRequest request;
        std::vector<GetReply> replyList;
        GetReply reply;
        while (stream->Read(&request)) {

            // cout<<map.count(request.key())<<endl;
 
            reply.set_value(map.Get_map(request.key()));
            //cout<<"Value: "<<reply.value()<<endl;
            stream->Write(reply);
            }

        return Status::OK;
    };


    Status KeyValueStoreImpl::deletekey(ServerContext* context, const DeleteRequest* request,DeleteReply* reply)
    {
        //cout<<map[request->key()]<<endl;
        //cout<<"Delete Connecting"<<endl;
        map.Delete_map(request->key());
        //cout<<map[request->key()]<<endl;
        return Status::OK;
    }


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
