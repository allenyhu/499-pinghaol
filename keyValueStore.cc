#include "keyValueStore.h"
using namespace std;
//insert a key value to the map
void KeyValueMap::Put_map(const std::string& key, const std::string& value) {
    mtx.lock();
    map[key] = value;
    mtx.unlock();
    return;
};

//check if the mao cointain this key
bool KeyValueMap::Contain_map (const std::string& key){
	mtx.lock();
	if(map.find(key) == map.end() )
    {
    	mtx.unlock();
    	return false;
    }else{
    	mtx.unlock();
        return true;
    }
    mtx.unlock();
    return false;
}

//Get the value for a giving keys
std::string KeyValueMap::Get_map (const std::string& key){
	mtx.lock();
	std::string  value = map[key];
	mtx.unlock();
	return value;

}

//delete a key and its value from the map
void KeyValueMap::Delete_map(const std::string& key) {
	mtx.lock();
	map.erase(key);
	mtx.unlock();
	return;
}