#include "serviceLayer.h"
#include <gtest/gtest.h>

int ServiceLayerImpliment::registeruser(std::string user1, KeyValueMap &store) {
  int contain = store.Contain_map(user1);
  if (contain == 1) {
    return 1;
  } else {
    std::string empty = "";
    store.Put_map(user1, empty);
    return 0;
  }
  return 1;
}

void ServiceLayerImpliment::setup(KeyValueMap &store) {
  std::string counter_key = "CHIRP_ID_COUNTER";
  std::string counter_value = "0";
  std::string check = store.Get_map(counter_key);
  if (check == "") {
    store.Put_map(counter_key, counter_value);
    counter = 0;
  } else {
    counter = stoi(store.Get_map(counter_key));
  }
}

int ServiceLayerImpliment::add(KeyValueMap &store) {
  std::string counter_key = "CHIRP_ID_COUNTER";
  std::string counter_value = "0";
  std::string check = store.Get_map(counter_key);
  if (check == "") {
    store.Put_map(counter_key, counter_value);
    counter = 0;
  }
  counter_value = store.Get_map(counter_key);
  counter = stoi(counter_value);
  counter++;
  counter_value = std::to_string(counter);
  store.Put_map(counter_key, counter_value);
  return counter;
}

int ServiceLayerImpliment::getID(KeyValueMap &store) {
  std::string counter_key = "CHIRP_ID_COUNTER";
  std::string counter_value = "0";
  std::string check = store.Get_map(counter_key);
  if (check == "") {
    store.Put_map(counter_key, counter_value);
    counter = 0;
  } else {
    counter_value = store.Get_map(counter_key);
    counter = stoi(counter_value);
  }
  return counter;
}

int ServiceLayerImpliment::follow(std::string user1, std::string user2,
                                  KeyValueMap &store) {
  std::string user = "U:" + user1;

  int contain1 = store.Contain_map(user1);
  int contain2 = store.Contain_map(user2);

  bool alreadyFollowing = false;
  if (contain1 == 1 && contain2 == 1) {
    Following follow;
    std::string curr_follow = store.Get_map(user);
    follow.ParseFromString(curr_follow);

    for (int i = 0; i < follow.username_size(); i++) {
      if (follow.username(i) == user2) {
        alreadyFollowing = true;
        return 2;
        break;
      }
    }

    if (!alreadyFollowing) {
      follow.add_username(user2);
      std::string *output = new std::string;
      follow.SerializeToString(output);
      store.Put_map(user, *output);
      delete output;
      return 1;
    }
  }
  return 0;
}

int ServiceLayerImpliment::chirp(std::string user1, std::string chirp,
                                 std::string parent, KeyValueMap &store) {
  getID(store);
  Chirp newChirp;
  
  std::string id = std::to_string(counter);
  std::string username = user1;
  Timestamp ts;
  std::string ts_str;
  MakeTimestamp(&ts_str);
  ts.ParseFromString(ts_str);

  newChirp.set_username(user1);
  newChirp.set_text(chirp);
  newChirp.set_parent_id(parent);
  newChirp.mutable_timestamp()->set_seconds(ts.seconds());
  newChirp.mutable_timestamp()->set_useconds(ts.useconds());
  newChirp.set_id(id);

  std::string *output1 = new std::string;
  newChirp.SerializeToString(output1);

  int contain1 = store.Contain_map(user1);
  int contain2 = store.Contain_map(parent);
  if (parent == "") {
    contain2 = 1;
  }
  if (contain1 == 1 && contain2 == 1) {
    store.Put_map(id, *output1);
    std::string curr_chirp = store.Get_map(username);
    curr_chirp += id;
    
    std::vector<std::string> tags = ParseTag(chirp);
    for (int i = 0; i < tags.size(); i++) {
      std::cout << tags[i] << std::endl;
      std::string* ts = new std::string;
      newChirp.mutable_timestamp()->SerializeToString(ts);
      AddTag(tags[i], *ts, id, store);
    }
    
    store.Put_map(username, curr_chirp);
    if (parent != "") {
      if (stoi(parent) <= counter) {
        std::cout << "curr id: " << counter << std::endl;
        Reply children;
        std::string parent_id = "R:" + parent;

        std::string curr_follow_id = store.Get_map(parent_id);
        children.ParseFromString(curr_follow_id);
        children.add_id(id);

        std::string *output2 = new std::string;
        children.SerializeToString(output2);
        store.Put_map(parent_id, *output2);
        delete output2;
      }
    }

    delete output1;
    add(store);
    return stoi(id);
  } else if (contain1 == 0) {
    return -1;
  } else if (contain2 == 0) {
    return -2;
  }
  return 0;
}

std::vector<std::string> ServiceLayerImpliment::read(std::string chirp_id,
                                                KeyValueMap &store) {
  std::vector<std::string> v;
  Chirp *readChirp = new Chirp;

  int contain = store.Contain_map(chirp_id);
  if (contain == 1) {
    std::queue<std::string> open_set;
    open_set.push(chirp_id);
    while (!open_set.empty()) {
      int size = open_set.size();
      for (int i = 0; i < size; i++) {
        std::string curr = open_set.front();
        open_set.pop();
        std::string s = store.Get_map(curr);
        readChirp->ParseFromString(s);
        std::string children_chrips = store.Get_map("R:" + readChirp->id());
        Reply children;
        children.ParseFromString(children_chrips);
        for (int i = 0; i < children.id_size(); i++) {
          open_set.push(children.id(i));
        }
        v.push_back(readChirp->text());
      }
    }
  }
  return v;
}

std::vector<std::string> ServiceLayerImpliment::monitor(std::string user1,
                                                        KeyValueMap &store) {
  std::vector<std::string> v;
  std::string username = user1;
  std::string follow = store.Get_map("U:" + user1);
  Following follow_user;
  follow_user.ParseFromString(follow);
  MonitorReply reply;

  std::vector<int> list;
  std::cout << "testing : " << follow_user.username_size() << std::endl;
  for (int i = 0; i < follow_user.username_size(); i++) {
    std::string ids = store.Get_map(follow_user.username(i));
    list.push_back(ids.length());
  }

  while (true) {
    for (int i = 0; i < follow_user.username_size(); i++) {
      std::string ids = store.Get_map(follow_user.username(i));
      for (int j = 0; j < ids.length(); j++) {
        std::string a;
        a.push_back(ids[j]);
        std::string str_chrip = store.Get_map(a);
        Chirp temp_chirp;
        temp_chirp.ParseFromString(str_chrip);
        reply.mutable_chirp()->set_username(temp_chirp.username());
        reply.mutable_chirp()->set_text(temp_chirp.text());
        reply.mutable_chirp()->set_id(temp_chirp.parent_id());
        reply.mutable_chirp()->set_parent_id(temp_chirp.parent_id());
        reply.mutable_chirp()->mutable_timestamp()->set_seconds(
            temp_chirp.timestamp().seconds());
        reply.mutable_chirp()->mutable_timestamp()->set_useconds(
            temp_chirp.timestamp().useconds());
        v.push_back(reply.mutable_chirp()->text());
      }
    }
    break;
  }
  return v;
}

std::vector<std::string> ServiceLayerImpliment::stream(const std::string& user,
                                                       const std::string& hashtag,
						       const std::string& time,
						       KeyValueMap& store) {
  int check_user = store.Contain_map(user);
  if (!check_user) {
    return std::vector<std::string>(); 
  }
  
  if (!store.Contain_map(hashtag + kStreamTimestampKey_)) {
    // No chirp with `hashtag` has been made yet
    return std::vector<std::string>();
  }

  std::vector<std::string> chirps = GetStreamChirps(hashtag, time, store);
  chirps.push_back("test"); // TODO: implement stream functionality

  return chirps;
}

std::vector<std::string> ServiceLayerImpliment::GetStreamChirps(const std::string& hashtag,
                                                                const std::string& time,
								KeyValueMap& store) {
  std::vector<std::string> chirps;
  
  Timestamp curr_ts;
  curr_ts.ParseFromString(time);
  StreamTimes times;
  times.ParseFromString(store.Get_map(hashtag + kStreamTimestampKey_));

  Timestamp latest_ts;
  std::string latest_ts_str;

  for (int i = times.timestamp_size() - 1; i >= 0; i--) {
    latest_ts_str = times.timestamp(i);
    latest_ts.ParseFromString(latest_ts_str);
    std::string entries_str = store.Get_map(hashtag + "-" + latest_ts_str);
    auto curr_chirps = ParseStreamEntries(entries_str, time, store);
    
    // appending to front of chirps
    chirps.insert(chirps.begin(), curr_chirps.begin(), curr_chirps.end()); 
    
    // Due to reverse chron order, know that this if statement will be entered on 1st instance of latest_ts being older than curr_ts
    // Will only break after ParsingStreamEntries on 1st instance entry because of possibility an entry in bracket is after curr_time
    if (!(curr_ts.seconds() <= latest_ts.seconds() && curr_ts.useconds() <= latest_ts.useconds())) {
      break;
    }
  }

  return chirps;
}

std::vector<std::string> ServiceLayerImpliment::ParseStreamEntries(const std::string& entries_str, const std::string& time_str, KeyValueMap& store) {
  std::vector<std::string> chirps;

  StreamEntries entries;
  entries.ParseFromString(entries_str);
  Timestamp ts;
  ts.ParseFromString(time_str);

  // Move from most to least recent chirp
  for (int i = entries.streamdata_size() - 1; i >= 0; i--) {
    StreamData data = entries.streamdata(i);
    Timestamp data_ts = data.timestamp();

    if (ts.seconds() <= data_ts.seconds() && ts.useconds() <= data_ts.useconds()) {
      std::string chirp = store.Get_map(data.chirp_id()); 
      chirps.insert(chirps.begin(), chirp); // Maintain chronological order
    } else {
      break; // All following chirps will be older than `time_str`
    }
  }

  return chirps;
}

std::vector<std::string> ServiceLayerImpliment::ParseTag(const std::string& message) {
  std::vector<std::string> tags;
  std::string txt = message;
  size_t index = 0;
  std::string word;

  while ((index = txt.find(" ")) != std::string::npos) {
    word = txt.substr(0, index);
    if (!word.empty() && word.at(0) == '#') {
      tags.push_back(word);
    }
    txt = txt.substr(index + 1);
  }

  // Used when hashtag is only text
  if (!txt.empty() && txt.at(0) == '#') {
    tags.push_back(txt);
  }

  return tags;
}

void ServiceLayerImpliment::AddTag(const std::string& hashtag, const std::string& time, const std::string& id, KeyValueMap& store) {
  StreamTimes timestamps;
  StreamEntries stream_info; 
  Timestamp curr_time;
  curr_time.ParseFromString(time);

  std::string ts_key = hashtag + kStreamTimestampKey_; 
  std::string entry_key;

  // Get existing info if already exists in store
  if (store.Contain_map(ts_key)) {
    timestamps.ParseFromString(store.Get_map(ts_key));
    std::string latest_ts = timestamps.timestamp(timestamps.timestamp_size() - 1);
    entry_key = hashtag + "-" + latest_ts;
    std::string streams_str = store.Get_map(entry_key); 
    stream_info.ParseFromString(streams_str);
  } else {
    // First chirp with `tag`
    // `time` will be the "latest" timestamp
    entry_key = hashtag + "-" + time;
    timestamps.add_timestamp(time);

    std::string* timestamps_str = new std::string();
    timestamps.SerializeToString(timestamps_str);
    store.Put_map(ts_key, *timestamps_str);
    delete timestamps_str;
  }
  
  if (stream_info.streamdata_size() < kStreamTimestampSize_) {
    // Add data to current steam info entry
    StreamData* temp_data = stream_info.add_streamdata();
    temp_data->set_chirp_id(id);
    temp_data->mutable_timestamp()->set_seconds(curr_time.seconds());
    temp_data->mutable_timestamp()->set_useconds(curr_time.useconds()); 

    std::string* stream_info_str = new std::string();
    stream_info.SerializeToString(stream_info_str);
    store.Put_map(entry_key, *stream_info_str);
    
    delete stream_info_str;
  } else { 
    // Make new StreamEntries under new key
    StreamEntries new_entries;
    StreamData* temp_data = new_entries.add_streamdata();
    temp_data->set_chirp_id(id);
    temp_data->mutable_timestamp()->set_seconds(curr_time.seconds());
    temp_data->mutable_timestamp()->set_useconds(curr_time.useconds());

    entry_key = hashtag + "-" + time; // New entry will be in `time` bracket 
    std::string* new_entries_str = new std::string();
    new_entries.SerializeToString(new_entries_str);
    store.Put_map(entry_key, *new_entries_str);

    // Need to update timestamp key with new entry
    timestamps.add_timestamp(time);
    std::string* timestamps_str = new std::string();
    timestamps.SerializeToString(timestamps_str);
    store.Put_map(ts_key, *timestamps_str);
    
    delete new_entries_str;
    delete timestamps_str;
  }
}

void ServiceLayerImpliment::MakeTimestamp(std::string* ts_str) {
  Timestamp ts;
  timeval t;
  gettimeofday(&t, nullptr);
  ts.set_seconds(t.tv_sec);
  ts.set_useconds(t.tv_usec);

  ts.SerializeToString(ts_str);
}	
