#include "serviceClient.h"

// Register a user
void ServiceLayerClient::registeruser(std::string user) {
  ClientContext context;

  RegisterRequest request;
  request.set_username(user);
  RegisterReply reply;

  Status status = stub_->registeruser(&context, request, &reply);

  if (status.ok()) {
    if (reply.contain() == 1) {
      cout << "User already exist" << endl;
    } else {
      cout << "Register success" << endl;
    }
  } else {
    cout << "fail" << endl;
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
  }
}

// Follow a user
void ServiceLayerClient::follow(std::string user1, std::string user2) {
  ClientContext context;

  FollowRequest request;
  request.set_username(user1);
  request.set_to_follow(user2);
  FollowReply reply;

  Status status = stub_->follow(&context, request, &reply);
  if (status.ok()) {
    if (reply.contain() == 1) {
      cout << "Follow success" << endl;
    }
    // Check if user1 followed user2
    else if (reply.contain() == 2) {
      cout << user1 << " already flowwing " << user2 << endl;
    }
    // User1 or User 2 doesn't exist
    else {
      cout << "User doesn't esist" << endl;
    }
  } else {
    cout << "fail" << endl;
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
  }
}

// Post a chirp
void ServiceLayerClient::chirp(std::string username, std::string text,
                               std::string replyID) {
  ClientContext context;

  ChirpRequest request;
  request.set_username(username);
  request.set_text(text);
  request.set_parent_id(replyID);
  ChirpReply reply;

  Status status = stub_->chirp(&context, request, &reply);

  if (status.ok()) {
    if (reply.contain() == 0) {
      cout << "No such user" << endl;
    } else if (reply.contain() == -1) {
      cout << "No such parent chirp" << endl;
    } else {
      cout << "Post success, chirp id for this chirp is: " << reply.chirp().id()
           << endl;
    }
  } else {
    cout << "fail" << endl;
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
  }
}

// Read a chirp
void ServiceLayerClient::read(int id) {
  ClientContext context;
  ReadRequest request;
  request.set_chirp_id(to_string(id));
  ReadReply reply;

  Status status = stub_->read(&context, request, &reply);
  if (status.ok()) {
    if (reply.contain() == 0) {
      cout << "No such Chirp" << endl;
    } else {
      for (int i = 0; i < reply.chirps().size(); i++) {
        cout << "Reading chirps posted by " << reply.chirps(i).username();
        cout << " at time " << reply.chirps(i).timestamp().seconds();
        cout << ": \n\n    ";
        cout << reply.chirps(i).text() << endl;
        cout << "\n";
      }
    }
  } else {
    std::cout << "Read rpc failed." << std::endl;
  }
}

// Monitor a user
void ServiceLayerClient::monitor(std::string username) {
  MonitorRequest request;
  ClientContext context;
  MonitorReply reply;

  request.set_username(username);
  std::unique_ptr<ClientReader<MonitorReply> > reader(
      stub_->monitor(&context, request));
  std::cout << "Start monitoring " << endl;
  while (reader->Read(&reply)) {
    cout << reply.chirp().username() << " at time "
         << reply.chirp().timestamp().seconds() << " : " << reply.chirp().text()
         << endl;
  }
  Status status = reader->Finish();
  if (status.ok()) {
    std::cout << "ListFeatures rpc succeeded." << std::endl;
  } else {
    std::cout << "ListFeatures rpc failed." << std::endl;
  }
}

void ServiceLayerClient::stream(std::string username, std::string hashtag) {
  StreamRequest request;
  ClientContext context;
  StreamReply reply;

  request.set_username(username);
  request.set_hashtag(hashtag);

  std::unique_ptr<ClientReader<StreamReply> > reader(
      stub_->stream(&context, request));

  std::cout << username << " streaming: " << hashtag << std::endl;
  while (reader->Read(&reply)) {
    std::cout << reply.chirp().username() << " at time "
              << reply.chirp().timestamp().seconds() << " : "
              << reply.chirp().text() << std::endl;
  }

  Status status = reader->Finish();
  if (status.ok()) {
    std::cout << "Stream rpc succeeded." << std::endl;
  } else {
    std::cout << "Stream rpc ended. User terminated or please check user is "
                 "registered"
              << std::endl;
  }
}
