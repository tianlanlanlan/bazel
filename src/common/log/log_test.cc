#include "src/common/log/log.h"

#include "gtest/gtest.h"

TEST(LogTest, BasicLogging) {
    PNC_LOG_INFO("This is an info log from PNC component: {}", 42);
    PNC_LOG_WARN("This is a warning log from PNC component: {}", "be careful!");
    PNC_LOG_ERROR("This is an error log from PNC component: error code {}", -1);
}