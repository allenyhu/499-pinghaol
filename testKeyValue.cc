#include "keyValueServerObject.h"
#include <gtest/gtest.h>

TEST(KeyValueTest, GetEmptyKey) {
    KeyValueStoreImplment store;
  EXPECT_EQ("", store.get("test"));
}

 TEST(KeyValueTest, SimplePut) {
    KeyValueStoreImplment store;
   store.put("test1", "test2");
   EXPECT_EQ("test2", store.get("test1"));
 }

 TEST(KeyValueTest, MultiplePutAndGet) {
    KeyValueStoreImplment store;
   store.put("test1", "test2");
   store.put("test3", "test4");

   EXPECT_EQ("test4", store.get("test3"));
 }

TEST(KeyValueTest, SimpleDelete) {
    KeyValueStoreImplment store;
    store.put("test1", "test2");
    store.delete("test1");
    
    EXPECT_EQ("", store.get("test1"));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
