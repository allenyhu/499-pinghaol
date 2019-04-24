#include <gtest/gtest.h>
#include "keyValueStore.h"

// Test get empty value string
TEST(KeyValueTest, GetEmptyKey) {
  KeyValueMap store;
  EXPECT_EQ("", store.Get_map("test"));
}

// Simple put
TEST(KeyValueTest, SimplePut) {
  KeyValueMap store;
  store.Put_map("test1", "test2");
  EXPECT_EQ("test2", store.Get_map("test1"));
}

// Multiple put and get
TEST(KeyValueTest, MultiplePutAndGet) {
  KeyValueMap store;
  store.Put_map("test1", "test2");
  store.Put_map("test3", "test4");
  EXPECT_EQ("test4", store.Get_map("test3"));
}

// Delete value from key
TEST(KeyValueTest, SimpleDelete) {
  KeyValueMap store;
  store.Put_map("test1", "test2");
  store.Delete_map("test1");
  EXPECT_EQ("", store.Get_map("test1"));
}

// Put and delete and put
TEST(KeyValueTest, PutDeletePut) {
  KeyValueMap store;
  store.Put_map("test1", "test2");
  store.Delete_map("test1");
  store.Put_map("test1", "test3");
  EXPECT_EQ("test3", store.Get_map("test1"));
}

// Key Value Store testing
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
