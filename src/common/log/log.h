/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include <sstream>
#include <cstdlib>

#include <spdlog/spdlog.h>

// Keep glog CHECK macros (CHECK_GT, CHECK_GE, CHECK_NOTNULL, etc.)
// throughout the codebase.  Logging itself uses spdlog (see AINFO etc. below).
#include <glog/logging.h>

#define LEFT_BRACKET "["
#define RIGHT_BRACKET "]"

#ifndef MODULE_NAME
#define MODULE_NAME "pnc"
#endif

namespace apollo {
namespace log {

// Stream-style log helper that captures source location and logs via spdlog.
class LogStream {
public:
    LogStream(const char* file, int line, spdlog::level::level_enum level)
        : file_(file), line_(line), level_(level) {}

    ~LogStream() {
        if (auto logger = spdlog::default_logger_raw()) {
            logger->log(
                spdlog::source_loc{file_, line_, nullptr},
                level_, buf_.str());
        }
    }

    LogStream(const LogStream&) = delete;
    LogStream& operator=(const LogStream&) = delete;

    template <typename T>
    LogStream& operator<<(const T& v) {
        buf_ << v;
        return *this;
    }

    LogStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
        manip(buf_);
        return *this;
    }

private:
    std::ostringstream buf_;
    const char* file_;
    int line_;
    spdlog::level::level_enum level_;
};

}  // namespace log
}  // namespace apollo

// ──────────────────────────────────────────────────────────────────────────────
//  Logging macros — file and line are captured at the call site
// ──────────────────────────────────────────────────────────────────────────────

#define ADEBUG_MODULE(module) \
    apollo::log::LogStream(__FILE__, __LINE__, spdlog::level::debug)
#define ADEBUG  ADEBUG_MODULE(MODULE_NAME)
#define AINFO   apollo::log::LogStream(__FILE__, __LINE__, spdlog::level::info)
#define AWARN   apollo::log::LogStream(__FILE__, __LINE__, spdlog::level::warn)
#define AERROR  apollo::log::LogStream(__FILE__, __LINE__, spdlog::level::err)
#define AFATAL  apollo::log::LogStream(__FILE__, __LINE__, spdlog::level::critical)

// ──────────────────────────────────────────────────────────────────────────────
//  Conditional logging
// ──────────────────────────────────────────────────────────────────────────────

#define AINFO_IF(cond)  ALOG_IF(INFO, cond)
#define AWARN_IF(cond)  ALOG_IF(WARN, cond)
#define AERROR_IF(cond) ALOG_IF(ERROR, cond)
#define AFATAL_IF(cond) ALOG_IF(FATAL, cond)

#define ALOG_IF(severity, cond)                                              \
    !(cond) ? (void)0                                                        \
            : apollo::log::LogStream(__FILE__, __LINE__, spdlog::level::severity)

// ──────────────────────────────────────────────────────────────────────────────
//  CHECK – logs a failure then aborts
// ──────────────────────────────────────────────────────────────────────────────

#define ACHECK(cond)                                                         \
    if (!(cond)) {                                                           \
        apollo::log::LogStream(__FILE__, __LINE__, spdlog::level::critical)  \
            << "ACHECK failed: " #cond;                                      \
        std::abort();                                                        \
    }

// ──────────────────────────────────────────────────────────────────────────────
//  Convenience guards
// ──────────────────────────────────────────────────────────────────────────────

#if !defined(RETURN_IF_NULL)
#define RETURN_IF_NULL(ptr)                                                  \
    if (ptr == nullptr) {                                                    \
        AWARN << #ptr << " is nullptr.";                                     \
        return;                                                              \
    }
#endif

#if !defined(RETURN_VAL_IF_NULL)
#define RETURN_VAL_IF_NULL(ptr, val)                                         \
    if (ptr == nullptr) {                                                    \
        AWARN << #ptr << " is nullptr.";                                     \
        return val;                                                          \
    }
#endif

#if !defined(RETURN_IF)
#define RETURN_IF(condition)                                                 \
    if (condition) {                                                         \
        AWARN << #condition << " is met.";                                   \
        return;                                                              \
    }
#endif

#if !defined(RETURN_VAL_IF)
#define RETURN_VAL_IF(condition, val)                                        \
    if (condition) {                                                         \
        AWARN << #condition << " is met.";                                   \
        return val;                                                          \
    }
#endif

#if !defined(_RETURN_VAL_IF_NULL2__)
#define _RETURN_VAL_IF_NULL2__
#define RETURN_VAL_IF_NULL2(ptr, val)                                        \
    if (ptr == nullptr) {                                                    \
        return (val);                                                        \
    }
#endif

#if !defined(_RETURN_VAL_IF2__)
#define _RETURN_VAL_IF2__
#define RETURN_VAL_IF2(condition, val)                                       \
    if (condition) {                                                         \
        return (val);                                                        \
    }
#endif

#if !defined(_RETURN_IF2__)
#define _RETURN_IF2__
#define RETURN_IF2(condition)                                                \
    if (condition) {                                                         \
        return;                                                              \
    }
#endif
