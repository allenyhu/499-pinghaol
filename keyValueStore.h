#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

// Map for key value store
class KeyValueMap {
 public:
  // insert a key value to the map
  void Put_map(const std::string& key, const std::string& value);

  // check if the mao cointain this key
  bool Contain_map(const std::string& key);

  // Get the value for a giving keys
  std::string Get_map(const std::string& key);

  // delete a key and its value from the map
  void Delete_map(const std::string& key);

 private:
  std::unordered_map<std::string, std::string> map;
  std::mutex mtx;
};
