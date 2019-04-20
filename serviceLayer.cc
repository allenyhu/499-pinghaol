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
  unsigned long long time =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  std::string id = std::to_string(counter);
  std::string username = user1;
  newChirp.set_username(user1);
  newChirp.set_text(chirp);
  newChirp.set_parent_id(parent);
  newChirp.mutable_timestamp()->set_seconds(time / 1000);
  newChirp.mutable_timestamp()->set_useconds(time);
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
						       KeyValueMap& store) {
  int check_user = store.Contain_map(user);
  if (!check_user) {
    return std::vector<std::string>();
  }
  std::vector<std::string> chirps;
  chirps.push_back("test"); // TODO: implement stream functionality

  return chirps;
}

std::vector<std::string> ServiceLayerImpliment::ParseTag(const std::string& message) {
  //TODO: implement parsing
  
  return std::vector<std::string>();
}
