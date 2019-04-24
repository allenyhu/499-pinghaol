#include "serviceServer.h"

// Initialize Key Value Object
KeyValueStoreClient store(
    grpc::CreateChannel("localhost:50000", grpc::InsecureChannelCredentials()));

// Register a user
Status ServiceLayerImpl::registeruser(ServerContext* context,
                                      const RegisterRequest* request,
                                      RegisterReply* reply) {
  int contain = store.contain(request->username());

  if (contain == 1) {
    // User already exist
    reply->set_contain(1);
  } else {
    // User doesn't exist
    reply->set_contain(0);
    string user = request->username();
    string empty = "";
    store.put(user, empty);
  }
  return Status::OK;
}

// Setup initial value for chirp id
void ServiceLayerImpl::setup() {
  string counter_key = "CHIRP_ID_COUNTER";
  string counter_value = "0";
  string check = store.get(counter_key);
  if (check == "") {
    store.put(counter_key, counter_value);
    counter = 0;
  } else {
    counter = stoi(store.get(counter_key));
  }
}

// Storing chirp id
int ServiceLayerImpl::add() {
  string counter_key = "CHIRP_ID_COUNTER";
  string counter_value = "0";
  string check = store.get(counter_key);
  if (check == "") {
    store.put(counter_key, counter_value);
    counter = 0;
  }
  counter_value = store.get(counter_key);
  counter = stoi(counter_value);
  counter++;
  counter_value = to_string(counter);
  store.put(counter_key, counter_value);
  return counter;
}

// Check current chirp id
int ServiceLayerImpl::getID() {
  string counter_key = "CHIRP_ID_COUNTER";
  string counter_value = "0";
  string check = store.get(counter_key);
  if (check == "") {
    store.put(counter_key, counter_value);
    counter = 0;
  } else {
    counter_value = store.get(counter_key);
    counter = stoi(counter_value);
  }
  return counter;
}

// User 1 follow user 2
Status ServiceLayerImpl::follow(ServerContext* context,
                                const FollowRequest* request,
                                FollowReply* reply) {
  string user1 = "U:" + request->username();
  string user2 = request->to_follow();

  // Check if user1 and user 2 exist.
  int contain1 = store.contain(request->username());
  int contain2 = store.contain(user2);

  bool alreadyFollowing = false;
  if (contain1 == 1 && contain2 == 1) {
    Following follow;
    string curr_follow = store.get(user1);
    follow.ParseFromString(curr_follow);

    for (int i = 0; i < follow.username_size(); i++) {
      if (follow.username(i) == user2) {
        alreadyFollowing = true;
        reply->set_contain(2);
        // cout<<user1<<" already follow "<<user2<<endl;
        break;
      }
    }

    if (!alreadyFollowing) {
      follow.add_username(user2);
      reply->set_contain(1);
      string* output = new string;
      follow.SerializeToString(output);
      store.put(user1, *output);
      delete output;
    }
  } else {
    reply->set_contain(0);
  }

  return Status::OK;
}

// Post chirp
Status ServiceLayerImpl::chirp(ServerContext* context,
                               const ChirpRequest* request, ChirpReply* reply) {
  getID();
  Chirp newChirp;

  string id = to_string(counter);
  string username = request->username();
  Timestamp ts;
  std::string ts_str;
  MakeTimestamp(&ts_str);
  ts.ParseFromString(ts_str);

  newChirp.set_username(request->username());
  newChirp.set_text(request->text());
  newChirp.set_parent_id(request->parent_id());
  newChirp.mutable_timestamp()->set_seconds(ts.seconds());
  newChirp.mutable_timestamp()->set_useconds(ts.useconds());
  newChirp.set_id(id);

  string* output1 = new string;
  newChirp.SerializeToString(output1);

  // check if user exist and if replying chirp exist
  int contain1 = store.contain(request->username());
  int contain2 = store.contain(request->parent_id());
  if (request->parent_id() == "") {
    contain2 = 1;
  }
  if (contain1 == 1 && contain2 == 1) {
    reply->set_contain(1);
    store.put(id, *output1);
    string curr_chirp = store.get(username);
    curr_chirp += id;

    // Stream bookkeeping setup
    std::vector<std::string> tags = ParseTag(newChirp.text());
    for (int i = 0; i < tags.size(); i++) {
      std::string ts;
      newChirp.mutable_timestamp()->SerializeToString(&ts);
      AddTag(tags[i], ts, id);
    }

    store.put(username, curr_chirp);
    // cout<<"Posting Chirp"<<endl;
    reply->mutable_chirp()->set_id(id);
    if (request->parent_id() != "") {
      if (stoi(request->parent_id()) <= counter) {
        Reply children;
        string parent_id = "R:" + request->parent_id();

        string curr_follow_id = store.get(parent_id);
        children.ParseFromString(curr_follow_id);
        children.add_id(id);

        string* output2 = new string;
        children.SerializeToString(output2);
        store.put(parent_id, *output2);
        delete output2;
      }
    }
    delete output1;
    add();
  } else if (contain1 == 0) {
    // user doesn't exist
    reply->set_contain(0);
  } else if (contain2 == 0) {
    // Parent chirp doesn't exist
    reply->set_contain(-1);
  }

  return Status::OK;
}

std::vector<std::string> ServiceLayerImpl::ParseTag(
    const std::string& message) {
  std::vector<std::string> tags;
  std::string txt = message;
  size_t index = 0;
  std::string word;

  while ((index = txt.find(" ")) != std::string::npos) {
    word = txt.substr(0, index);
    if (!word.empty() && word.at(0) == '#' &&
        word.size() > 1) {  // don't accept just #
      tags.push_back(word);
    }
    txt = txt.substr(index + 1);
  }

  // Used when hashtag is only text
  if (!txt.empty() && txt.at(0) == '#' && txt.size() > 1) {
    tags.push_back(txt);
  }

  return tags;
}

void ServiceLayerImpl::AddTag(const std::string& hashtag,
                              const std::string& time_str,
                              const std::string& id) {
  StreamTimes timestamps;
  StreamEntries stream_info;
  std::string ts_key = hashtag + kStreamTimestampKey_;
  std::string entry_key;

  // Get existing info if already exists in store
  if (store.contain(ts_key)) {
    timestamps.ParseFromString(store.get(ts_key));
    std::string latest_ts =
        timestamps.timestamp(timestamps.timestamp_size() - 1);
    entry_key = hashtag + "-" + latest_ts;
    std::string streams_str = store.get(entry_key);
    stream_info.ParseFromString(streams_str);
  } else {
    // First chirp with `hashtag`
    // `time` will be the "latest" timestamp
    entry_key = hashtag + "-" + time_str;
    timestamps.add_timestamp(time_str);

    std::string timestamps_str;
    timestamps.SerializeToString(&timestamps_str);
    store.put(ts_key, timestamps_str);
  }

  if (stream_info.streamdata_size() < kStreamTimestampSize_) {
    AddStreamEntry(&stream_info, id, time_str, entry_key);
  } else {
    // Make new StreamEntries under new key
    StreamEntries new_entries;
    entry_key = hashtag + "-" + time_str;
    AddStreamEntry(&new_entries, id, time_str, entry_key);

    // Need to update timestamp key with new entry
    timestamps.add_timestamp(time_str);
    std::string timestamps_str;
    timestamps.SerializeToString(&timestamps_str);
    store.put(ts_key, timestamps_str);
  }
}

void ServiceLayerImpl::AddStreamEntry(StreamEntries* stream_info,
                                      const std::string& id,
                                      const std::string& time_str,
                                      std::string key) {
  Timestamp time;
  time.ParseFromString(time_str);

  StreamData* data = stream_info->add_streamdata();
  data->set_chirp_id(id);
  data->mutable_timestamp()->set_seconds(time.seconds());
  data->mutable_timestamp()->set_useconds(time.useconds());

  std::string stream_info_str;
  stream_info->SerializeToString(&stream_info_str);
  store.put(key, stream_info_str);
}

// Reading a chirp
Status ServiceLayerImpl::read(ServerContext* context,
                              const ReadRequest* request, ReadReply* reply) {
  // cout<<"Reading Chirp"<<endl;
  Chirp* readChirp = new Chirp;

  int contain = store.contain(request->chirp_id());
  if (contain == 1) {
    string curr = request->chirp_id();
    // queue to store child chirp
    queue<string> open_set;
    open_set.push(curr);
    reply->set_contain(1);
    while (!open_set.empty()) {
      int size = open_set.size();
      for (int i = 0; i < size; i++) {
        string curr = open_set.front();
        open_set.pop();
        string s = store.get(curr);
        readChirp = reply->add_chirps();
        readChirp->ParseFromString(s);

        string children_chrips = store.get("R:" + readChirp->id());

        Reply children;
        children.ParseFromString(children_chrips);
        for (int i = 0; i < children.id_size(); i++) {
          open_set.push(children.id(i));
        }
      }
    }
  } else {
    reply->set_contain(0);
  }
  return Status::OK;
}

// Monitoring a user
Status ServiceLayerImpl::monitor(ServerContext* context,
                                 const MonitorRequest* request,
                                 ServerWriter<MonitorReply>* writer) {
  // cout<<"monitoring"<<endl;
  string username = request->username();
  string follow = store.get("U:" + request->username());
  Following follow_user;
  follow_user.ParseFromString(follow);
  MonitorReply reply;

  // List to store the length of the user name
  vector<int> list;
  // cout<<"testing : "<<follow_user.username_size()<<endl;
  for (int i = 0; i < follow_user.username_size(); i++) {
    string ids = store.get(follow_user.username(i));
    list.push_back(ids.length());
  }

  // Loop for monitoring
  while (true) {
    for (int i = 0; i < follow_user.username_size(); i++) {
      string ids = store.get(follow_user.username(i));
      if (list[i] < ids.length()) {
        for (int j = list[i]; j < ids.length(); j++) {
          string a;
          a.push_back(ids[j]);
          string str_chrip = store.get(a);
          Chirp temp_chirp;
          temp_chirp.ParseFromString(str_chrip);
          reply.mutable_chirp()->set_username(temp_chirp.username());
          reply.mutable_chirp()->set_text(temp_chirp.text());
          reply.mutable_chirp()->set_id(temp_chirp.id());
          reply.mutable_chirp()->set_parent_id(temp_chirp.parent_id());
          reply.mutable_chirp()->mutable_timestamp()->set_seconds(
              temp_chirp.timestamp().seconds());
          reply.mutable_chirp()->mutable_timestamp()->set_useconds(
              temp_chirp.timestamp().useconds());
          writer->Write(reply);
        }
        list[i] = ids.length();
      }
      // Stop the loop
      if (context->IsCancelled()) {
        break;
      }
    }
    // Stop the loop
    if (context->IsCancelled()) {
      break;
    }
  }
  return Status::OK;
}

Status ServiceLayerImpl::stream(ServerContext* context,
                                const StreamRequest* request,
                                ServerWriter<StreamReply>* writer) {
  std::string username = request->username();
  std::string ts;
  MakeTimestamp(&ts);
  if (!store.contain(username)) {
    return Status::CANCELLED;
  }

  std::vector<std::string> chirp_strs;
  StreamReply reply;
  while (true) {
    if (store.contain(request->hashtag() + kStreamTimestampKey_)) {
      chirp_strs = GetStreamChirps(request->hashtag(), ts);
      MakeTimestamp(&ts);  // Update timestamp for next iteration
    }

    for (const std::string& chirp_str : chirp_strs) {
      Chirp chirp;
      chirp.ParseFromString(chirp_str);

      reply.mutable_chirp()->set_username(chirp.username());
      reply.mutable_chirp()->set_text(chirp.text());
      reply.mutable_chirp()->set_id(chirp.id());
      reply.mutable_chirp()->set_parent_id(chirp.parent_id());
      reply.mutable_chirp()->mutable_timestamp()->set_seconds(
          chirp.timestamp().seconds());
      reply.mutable_chirp()->mutable_timestamp()->set_useconds(
          chirp.timestamp().useconds());

      writer->Write(reply);
    }

    // Check if user killed stream()
    if (context->IsCancelled()) {
      break;
    }

    usleep(kStreamLoopDelay_);
  }
  return Status::OK;
}

std::vector<std::string> ServiceLayerImpl::GetStreamChirps(
    const std::string& hashtag, const std::string& time_str) {
  std::vector<std::string> chirps;

  Timestamp curr_ts;
  curr_ts.ParseFromString(time_str);
  StreamTimes times;
  times.ParseFromString(store.get(hashtag + kStreamTimestampKey_));

  Timestamp latest_ts;
  std::string latest_ts_str;

  for (int i = times.timestamp_size() - 1; i >= 0; i--) {
    latest_ts_str = times.timestamp(i);
    latest_ts.ParseFromString(latest_ts_str);
    std::string entries_str = store.get(hashtag + "-" + latest_ts_str);
    auto curr_chirps = ParseStreamEntries(entries_str, time_str);

    // Appending to front of `chirps`
    chirps.insert(chirps.begin(), curr_chirps.begin(), curr_chirps.end());

    // Due to reverse chron order of StreamTimes, know if statement will be
    // entered on 1st instance of latest_ts being older than curr_ts break after
    // ParsingStreamEntries on older entry because of possibility an entry in
    // bracket is after curr_time break to not check other older entries (only
    // want 1st instance)
    //
    // Check if curr_ts is older than latest_ts
    bool curr_ts_older = (curr_ts.seconds() < latest_ts.seconds()) ||
                         ((curr_ts.seconds() == latest_ts.seconds()) &&
                          (curr_ts.useconds() <= latest_ts.useconds()));
    if (!curr_ts_older) {
      break;
    }
  }

  return chirps;
}

std::vector<std::string> ServiceLayerImpl::ParseStreamEntries(
    const std::string& entries_str, const std::string& time_str) {
  std::vector<std::string> chirps;

  StreamEntries entries;
  entries.ParseFromString(entries_str);
  Timestamp ts;
  ts.ParseFromString(time_str);

  // Move from most recent to least recent chirp
  for (int i = entries.streamdata_size() - 1; i >= 0; i--) {
    StreamData data = entries.streamdata(i);
    Timestamp data_ts = data.timestamp();

    // Check if ts is older than data_ts
    bool ts_older = (ts.seconds() < data_ts.seconds()) ||
                    ((ts.seconds() == data_ts.seconds()) &&
                     (ts.useconds() <= data_ts.useconds()));
    if (ts_older) {
      std::string chirp = store.get(data.chirp_id());
      chirps.insert(chirps.begin(), chirp);
    } else {
      // All following chirps will be older than `time_str`, don't want to
      // iterate
      break;
    }
  }
  return chirps;
}

void ServiceLayerImpl::MakeTimestamp(std::string* ts_str) {
  Timestamp ts;
  timeval t;
  gettimeofday(&t, nullptr);
  ts.set_seconds(t.tv_sec);
  ts.set_useconds(t.tv_usec);

  ts.SerializeToString(ts_str);
}

void RunServer() {
  std::string server_address("0.0.0.0:50002");
  ServiceLayerImpl service;
  service.setup();
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
