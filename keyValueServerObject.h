#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>

#include <thread>
#include <mutex>

using namespace std;




class KeyValueStoreImplment {
public:
    void put(string key,string value){};
    
    bool contain (string key){};
    
    string get(string key) {};


    void deletekey(string key){};
    
private:
     unordered_map<string, string> map;
    mutex mtx;
};
