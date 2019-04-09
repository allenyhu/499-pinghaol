#include <gtest/gtest.h>
#include "serviceLayer.h"
using namespace std;

std::vector<std::string> users = {"username1", "username2",
                                        "username3", "username4"};

std::vector<std::string> chirps = {"Chirp1",	 
									"Chirp2",
                                 	"Chirp text 3",
                                	"Chirp text 4"};

//Simple register
TEST(ServiceTest, RegisterOneUser) {
	KeyValueMap store;
	ServiceLayerImpliment service;
  	EXPECT_EQ(0, service.registeruser(users[1],store));
}

//Register existing user
TEST(ServiceTest, RegieterExistingUser) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
  	EXPECT_EQ(1, service.registeruser(users[1],store));
}

//Multiple registration 1
TEST(ServiceTest, MultipleRegister1) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
  	EXPECT_EQ(0, service.registeruser(users[3],store));
}

//Multiple registration 2
TEST(ServiceTest, MultipleRegister2) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
  	EXPECT_EQ(1, service.registeruser(users[2],store));
}

//Check add chirp id function
TEST(ServiceTest, AddChirpID) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
  	EXPECT_EQ(1, service.add(store));
}

//Check multiple adding chirp id function
TEST(ServiceTest, AddMultipleChirpID) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.add(store);
	service.add(store);
  	EXPECT_EQ(3, service.add(store));
}

//Check follow user function
TEST(ServiceTest, SimpleTestFollow) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
  	EXPECT_EQ(1, service.follow(users[1],users[2],store));
}

//Test following whenUser 2 is not registered
TEST(ServiceTest, FollowNotExistUser2) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
  	EXPECT_EQ(0, service.follow(users[1],users[2],store));
}

//Test following when User 1 is not registered
TEST(ServiceTest, FollowNotExistUser1) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[2],store);
  	EXPECT_EQ(0, service.follow(users[1],users[2],store));
}

//User1 Already follow User2
TEST(ServiceTest, AlreadyFollow) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
	service.follow(users[1],users[2],store);
  	EXPECT_EQ(2, service.follow(users[1],users[2],store));
}

//Simple posting
TEST(ServiceTest, SimplePost) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
  	EXPECT_EQ(0, service.chirp(users[1],chirps[1],"",store));
}

//Multiple posting
TEST(ServiceTest, MultiplePost) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.chirp(users[1],chirps[1],"",store);
  	EXPECT_EQ(1, service.chirp(users[1],chirps[3],"",store));
}

//Chirp with Parent
TEST(ServiceTest, ChirpWithParent) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.chirp(users[1],chirps[1],"",store);
	service.chirp(users[1],chirps[2],"0",store);
  	EXPECT_EQ(2, service.chirp(users[1],chirps[3],"1",store));
}


//Unregister Usere post Chirp
TEST(ServiceTest, UnregisterUserChirp) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.chirp(users[1],chirps[1],"",store);
	service.chirp(users[1],chirps[2],"0",store);
  	EXPECT_EQ(-1, service.chirp(users[2],chirps[3],"",store));
}


//Chirp with Parent that dees not exist
TEST(ServiceTest, ChirpWithParentNotExist) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.chirp(users[1],chirps[1],"",store);
	service.chirp(users[1],chirps[2],"0",store);
  	EXPECT_EQ(-2, service.chirp(users[1],chirps[3],"5",store));
}

//Simple Read chirp
TEST(ServiceTest, SimpleRead) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.chirp(users[1],chirps[1],"",store);
	std::vector<std::string> v = service.read("0",store);
  	EXPECT_EQ(chirps[1], v[0]);
}

//Posting multiple chirps and read
TEST(ServiceTest, ReadFromDefferentID) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.chirp(users[1],chirps[0],"",store);
	service.chirp(users[1],chirps[1],"",store);
	std::vector<std::string> v = service.read("1",store);
  	EXPECT_EQ(chirps[1], v[0]);
}

//Read Chirps fowlloing other chirp1
TEST(ServiceTest, ReadChirpsWithParent1) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.chirp(users[1],chirps[0],"",store);
	service.chirp(users[1],chirps[1],"0",store);
	std::vector<std::string> v = service.read("1",store);
  	EXPECT_EQ(chirps[1], v[0]);
}

//Read Chirps fowlloing other chirp2
TEST(ServiceTest, ReadChirpsWithParent2) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.chirp(users[1],chirps[0],"",store);
	service.chirp(users[1],chirps[2],"0",store);
	service.chirp(users[1],chirps[3],"0",store);
	std::vector<std::string> v = service.read("2",store);
	cout<<v.size()<<endl;
  	EXPECT_EQ(chirps[3], v[0]);
  }

//Read Chirps from chirp that doesn't exist
TEST(ServiceTest, ReadNoneExistChirp) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.chirp(users[1],chirps[0],"",store);
	std::vector<std::string> v = service.read("1",store);
  	EXPECT_EQ(0, v.size());
}

//SimpleMonitorTest
TEST(ServiceTest, SimpleMonitor) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
	service.follow(users[1],users[2],store);
	service.chirp(users[2],chirps[0],"",store);
	service.chirp(users[2],chirps[1],"",store);
	service.chirp(users[2],chirps[2],"",store);
	std::vector<std::string> v = service.monitor(users[1],store);
  	EXPECT_EQ(3, v.size());
}

//SimpleMonitorTest 1
TEST(ServiceTest, SimpleMonitorCheckChirp1) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
	service.follow(users[1],users[2],store);
	service.chirp(users[2],chirps[0],"",store);
	service.chirp(users[2],chirps[1],"",store);
	service.chirp(users[2],chirps[2],"",store);
	std::vector<std::string> v = service.monitor(users[1],store);
  	EXPECT_EQ(chirps[0], v[0]);
}


//SimpleMonitorTest 2
TEST(ServiceTest, SimpleMonitorCheckChirp2) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
	service.follow(users[1],users[2],store);
	service.chirp(users[2],chirps[0],"",store);
	service.chirp(users[2],chirps[1],"",store);
	service.chirp(users[2],chirps[2],"",store);
	std::vector<std::string> v = service.monitor(users[1],store);
  	EXPECT_EQ(chirps[2], v[2]);
}

//Monitor multiple user 1
TEST(ServiceTest, MultipleMonitorCheckChirp1) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
	service.registeruser(users[3],store);
	service.follow(users[1],users[2],store);
	service.follow(users[1],users[3],store);
	service.chirp(users[2],chirps[0],"",store);
	service.chirp(users[2],chirps[1],"",store);
	service.chirp(users[3],chirps[2],"",store);
	service.chirp(users[3],chirps[3],"",store);
	std::vector<std::string> v = service.monitor(users[1],store);
  	EXPECT_EQ(4, v.size());
}

//Monitor multiple user 2
TEST(ServiceTest, MultipleMonitorCheckChirp2) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
	service.registeruser(users[3],store);
	service.follow(users[1],users[2],store);
	service.follow(users[1],users[3],store);
	service.chirp(users[2],chirps[0],"",store);
	service.chirp(users[2],chirps[1],"",store);
	service.chirp(users[3],chirps[2],"",store);
	service.chirp(users[3],chirps[3],"",store);
	std::vector<std::string> v = service.monitor(users[1],store);
  	EXPECT_EQ(chirps[0], v[0]);
}

//Monitor multiple user 3
TEST(ServiceTest, MultipleMonitorCheckChirp3) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
	service.registeruser(users[3],store);
	service.follow(users[1],users[2],store);
	service.follow(users[1],users[3],store);
	service.chirp(users[2],chirps[0],"",store);
	service.chirp(users[2],chirps[1],"",store);
	service.chirp(users[3],chirps[2],"",store);
	service.chirp(users[3],chirps[3],"",store);
	std::vector<std::string> v = service.monitor(users[1],store);
  	EXPECT_EQ(chirps[3], v[3]);
}

//Checking sequence of monitoring 1
TEST(ServiceTest, MultipleMonitorCheckChirpSequence1) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
	service.registeruser(users[3],store);
	service.follow(users[1],users[2],store);
	service.follow(users[1],users[3],store);
	service.chirp(users[2],chirps[0],"",store);
	service.chirp(users[3],chirps[2],"",store);
	service.chirp(users[2],chirps[1],"",store);
	service.chirp(users[3],chirps[3],"",store);
	std::vector<std::string> v = service.monitor(users[1],store);
  	EXPECT_EQ(chirps[3], v[3]);
}


//Checking sequence of monitoring 2
TEST(ServiceTest, MultipleMonitorCheckChirpSequence2) {
	KeyValueMap store;
  	ServiceLayerImpliment service;
	service.registeruser(users[1],store);
	service.registeruser(users[2],store);
	service.registeruser(users[3],store);
	service.follow(users[1],users[2],store);
	service.follow(users[1],users[3],store);
	service.chirp(users[2],chirps[0],"",store);
	service.chirp(users[3],chirps[2],"",store);
	service.chirp(users[2],chirps[1],"",store);
	service.chirp(users[3],chirps[3],"",store);
	std::vector<std::string> v = service.monitor(users[1],store);
  	EXPECT_EQ(chirps[2], v[2]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}