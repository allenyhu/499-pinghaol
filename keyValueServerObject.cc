#include "keyValueServerObject.h"

void KeyValueStoreImplment::put(string key, string value) {
  map[key] = value;
  return;
}

bool KeyValueStoreImplment::contain(string key) {
  cout << "Contain Connecting" << endl;
  if (map.find(key) == map.end()) {
    return false;
    cout << "key doesn't exist" << endl;
  } else {
    return true;
  }
  return false;
}

string KeyValueStoreImplment::get(string key) {
  cout << "Get Connecting" << endl;
  cout << "Contain Connecting" << endl;
  return map[key];
};

void KeyValueStoreImplment::deletekey(string key) {
  // cout<<map[request->key()]<<endl;
  cout << "Delete Connecting" << endl;
  map.erase(key);
  // cout<<map[request->key()]<<endl;
  return;
}
