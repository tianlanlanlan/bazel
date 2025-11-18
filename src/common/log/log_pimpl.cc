#include "src/common/log/log_pimpl.h"

#include "spdlog/sinks/dist_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <cstdarg>

class LogWrapperImpl {
  public:
    explicit LogWrapperImpl(const std::string &component_name) : component_name_(component_name) { InitializeLogger(); }

    ~LogWrapperImpl() {
        if (logger_) {
            spdlog::drop(component_name_);
        }
    }

    void Log(LogLevel level, const char *format, va_list args) {
        if (!logger_) {
            return;
        }

        auto spd_level = ConvertToSpdlogLevel(level);

        logger_->log(spd_level, format, args);
    }

  private:
    spdlog::level::level_enum ConvertToSpdlogLevel(LogLevel level) {
        switch (level) {
        case LogLevel::TRACE:
            return spdlog::level::trace;
        case LogLevel::DEBUG:
            return spdlog::level::debug;
        case LogLevel::INFO:
            return spdlog::level::info;
        case LogLevel::WARN:
            return spdlog::level::warn;
        case LogLevel::ERROR:
            return spdlog::level::err;
        case LogLevel::CRITICAL:
            return spdlog::level::critical;
        default:
            return spdlog::level::info;
        }
    }

    void InitializeLogger() {
        try {
            // 创建控制台 sink
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::info);

            // 创建文件 sink - 按大小滚动，最大 100MB，保留 3 个文件
            auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/" + component_name_ + ".log",
                                                                                    1024 * 1024 * 100, 3);
            file_sink->set_level(spdlog::level::trace);

            // 创建分布式 sink，组合多个 sink
            auto dist_sink = std::make_shared<spdlog::sinks::dist_sink_mt>();
            dist_sink->add_sink(console_sink);
            dist_sink->add_sink(file_sink);

            // 创建 logger
            logger_ = std::make_shared<spdlog::logger>(component_name_, dist_sink);

// 设置日志模式：异步还是同步
#ifdef SPDLOG_ASYNC_LOGGING
            spdlog::set_async_mode(8192); // 异步模式，队列大小 8192
#endif

            // 设置日志格式: [时间] [组件名] [级别] 消息
            logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
            logger_->set_level(spdlog::level::trace); // 设置最低日志级别
            logger_->flush_on(spdlog::level::warn);   // 在警告及以上级别时立即刷新

            // 注册 logger，这样可以通过 spdlog::get("name") 获取
            spdlog::register_logger(logger_);

        } catch (const spdlog::spdlog_ex &ex) {
            // 如果创建失败，使用默认的 logger
            logger_ = spdlog::stdout_color_mt(component_name_);
            logger_->error("Logger initialization failed for {}, using default: {}", component_name_, ex.what());
        }
    }

    std::string component_name_;
    std::shared_ptr<spdlog::logger> logger_;
};

// LogWrapper 实现
LogWrapper::LogWrapper(const std::string &component_name) : pimpl_(std::make_unique<LogWrapperImpl>(component_name)) {}

LogWrapper::~LogWrapper() = default;

void LogWrapper::Log(LogLevel level, const char *format, ...) {
    va_list args;
    va_start(args, format);
    pimpl_->Log(level, format, args);
    va_end(args);
}
