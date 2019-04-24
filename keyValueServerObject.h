#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <mutex>
#include <thread>

using namespace std;

class KeyValueStoreImplment {
 public:
  void put(string key, string value){};

  bool contain(string key){};

  string get(string key){};

  void deletekey(string key){};

 private:
  unordered_map<string, string> map;
  mutex mtx;
};
