#ifndef LOG_H
#define LOG_H

#include <cstdarg>
#include <memory>
#include <mutex>
#include <string>

// 日志级别枚举
enum class LogLevel { TRACE, DEBUG, INFO, WARN, ERROR, CRITICAL };

// 前向声明
class LogWrapperImpl;

// LogWrapper 类 - PIMPL 模式
class LogWrapper {
  public:
    explicit LogWrapper(const std::string &component_name);
    ~LogWrapper();

    // 禁用拷贝和移动
    LogWrapper(const LogWrapper &) = delete;
    LogWrapper &operator=(const LogWrapper &) = delete;
    LogWrapper(LogWrapper &&) = delete;
    LogWrapper &operator=(LogWrapper &&) = delete;

    void Log(LogLevel level, const char *format, ...);

  private:
    std::unique_ptr<LogWrapperImpl> pimpl_;
};

// 单例访问宏
#define GET_LOG_WRAPPER(component) LogWrapper##component::GetInstance()

// 为每个组件定义单例类的宏
#define DEFINE_COMPONENT_LOGGER(component)                                                                             \
    class LogWrapper##component {                                                                                      \
      public:                                                                                                          \
        static LogWrapper##component &GetInstance() {                                                                  \
            static LogWrapper##component instance;                                                                     \
            return instance;                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        void Log(LogLevel level, const char *format, ...) {                                                            \
            std::call_once(init_flag_, [this]() { wrapper_ = std::make_unique<::LogWrapper>(#component); });           \
                                                                                                                       \
            if (wrapper_) {                                                                                            \
                va_list args;                                                                                          \
                va_start(args, format);                                                                                \
                wrapper_->Log(level, format, args);                                                                    \
                va_end(args);                                                                                          \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
      private:                                                                                                         \
        LogWrapper##component() = default;                                                                             \
        ~LogWrapper##component() = default;                                                                            \
                                                                                                                       \
        std::unique_ptr<::LogWrapper> wrapper_;                                                                        \
        std::once_flag init_flag_;                                                                                     \
    };


#endif // LOG_H