#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv); // Initialize GTest
  return RUN_ALL_TESTS();               // Run all defined tests
}