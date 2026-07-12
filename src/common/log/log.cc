#include "src/common/log/log.h"

#include <spdlog/sinks/dist_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace {

struct LoggerInitializer {
    LoggerInitializer() {
        // Guard against double initialization when this translation unit
        // is linked into both the main binary and a dlopen'ed shared library.
        if (spdlog::default_logger_raw() != nullptr) {
            return;
        }
        try {
            // Console sink (INFO+)
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::info);

            // File sink – rotating, 100 MB per file, 3 backups (TRACE+)
            auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                "logs/pnc.log", 1024 * 1024 * 100, 3);
            file_sink->set_level(spdlog::level::trace);

            // Combine sinks
            auto dist_sink = std::make_shared<spdlog::sinks::dist_sink_mt>();
            dist_sink->add_sink(console_sink);
            dist_sink->add_sink(file_sink);

            // Logger
            auto logger = std::make_shared<spdlog::logger>("pnc", dist_sink);
            // Pattern: [timestamp] [file(line)] [level] message
            logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%s(%#)] [%l] %v");
            logger->set_level(spdlog::level::trace);
            logger->flush_on(spdlog::level::warn);

            spdlog::set_default_logger(logger);
        } catch (const spdlog::spdlog_ex& ex) {
            auto logger = spdlog::stdout_color_mt("pnc");
            logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%s(%#)] [%l] %v");
            spdlog::set_default_logger(logger);
            logger->error("Logger init fallback: {}", ex.what());
        }
    }
} logger_init;

}  // namespace
