#pragma once

#include <memory> // std::unique_ptr

namespace DnApp::Logger {
    /**
     * Use `debug(<message>)`, `info(<message>)`, `warning(<message>)`
     * `error(<message>)`, `critical(<message>)` in most cases.
     *
     * Use `log(<log level>, <message>)` when dynamic log level needed.
     *
     * For all logging methods, you can pass 2 types of messages:
     * `char[]` and `std::unique_ptr<char[]>`.
     */
    class Logger {
    public:
        enum struct LOG_LEVEL {
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            CRITICAL
        };

        static
        constexpr
        const char* const LOG_LEVELS[] = {
            "debug",
            "info",
            "warning",
            "error",
            "critical"
        };

        static
        auto logLevelToString(const LOG_LEVEL level) -> const char* {
            return LOG_LEVELS[static_cast<int>(level)];
        }

        virtual
        auto log(LOG_LEVEL level, const char* message) -> void = 0;

        // ATTENTION!
        // https://isocpp.org/wiki/faq/strange-inheritance#hiding-rule
        auto log(const LOG_LEVEL level, const std::unique_ptr<const char[]> message) -> void {
            log(level, message.get());
        }

        auto debug(const char* const message) -> void {
            log(LOG_LEVEL::DEBUG, message);
        };

        auto debug(const std::unique_ptr<const char[]> message) -> void {
            log(LOG_LEVEL::DEBUG, message.get());
        };

        auto info(const char* const message) -> void {
            log(LOG_LEVEL::INFO, message);
        };

        auto info(const std::unique_ptr<const char[]> message) -> void {
            log(LOG_LEVEL::INFO, message.get());
        };

        auto warning(const char* const message) -> void {
            log(LOG_LEVEL::WARNING, message);
        };

        auto warning(const std::unique_ptr<const char[]> message) -> void {
            log(LOG_LEVEL::WARNING, message.get());
        };

        auto error(const char* const message) -> void {
            log(LOG_LEVEL::ERROR, message);
        };

        auto error(const std::unique_ptr<const char[]> message) -> void {
            log(LOG_LEVEL::ERROR, message.get());
        };

        auto critical(const char* const message) -> void {
            log(LOG_LEVEL::CRITICAL, message);
        };

        auto critical(const std::unique_ptr<const char[]> message) -> void {
            log(LOG_LEVEL::CRITICAL, message.get());
        };
    };
}
