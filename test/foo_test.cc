#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

TEST(Test, TestFoo) {
    std::cout << "TestFoo" << std::endl;

    std::unordered_map<std::string, std::string> foo_map;

    foo_map["hello"] = "world";
    foo_map["nihao"] = "hahaha";
}
