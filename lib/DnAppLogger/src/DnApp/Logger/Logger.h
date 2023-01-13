#pragma once

#include <memory>

namespace DnApp::Logger {
    /**
     * Use `debug(<message>)`, `info(<message>)`, `warning(<message>)`
     * `error(<message>)`, `critical(<message>)` in most cases.
     *
     * Use `log(<log level>, <message>)` when dynamic log level needed.
     *
     * For all logging methods, you can pass 3 types of messages:
     * `char[]`, `const char[]` and `std::unique_ptr<char[]>`.
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
        const char* LOG_LEVELS[] = {
            "debug",
            "info",
            "warning",
            "error",
            "critical"
        };

        static
        const char* logLevelToString(LOG_LEVEL level) {
            return LOG_LEVELS[static_cast<int>(level)];
        }

        virtual
        void log(LOG_LEVEL level, char* message) = 0;

        virtual
        void log(LOG_LEVEL level, const char* message) = 0;

        // ATTENTION!
        // https://isocpp.org/wiki/faq/strange-inheritance#hiding-rule
        void log(LOG_LEVEL level, std::unique_ptr<char[]> message) {
            log(level, message.get());
        }

        void debug(char* message) {
            log(LOG_LEVEL::DEBUG, message);
        };

        void debug(const char* message) {
            log(LOG_LEVEL::DEBUG, message);
        };

        void debug(std::unique_ptr<char[]> message) {
            log(LOG_LEVEL::DEBUG, message.get());
        };

        void info(char* message) {
            log(LOG_LEVEL::INFO, message);
        };

        void info(const char* message) {
            log(LOG_LEVEL::INFO, message);
        };

        void info(std::unique_ptr<char[]> message) {
            log(LOG_LEVEL::INFO, message.get());
        };

        void warning(char* message) {
            log(LOG_LEVEL::WARNING, message);
        };

        void warning(const char* message) {
            log(LOG_LEVEL::WARNING, message);
        };

        void warning(std::unique_ptr<char[]> message) {
            log(LOG_LEVEL::WARNING, message.get());
        };

        void error(char* message) {
            log(LOG_LEVEL::ERROR, message);
        };

        void error(const char* message) {
            log(LOG_LEVEL::ERROR, message);
        };

        void error(std::unique_ptr<char[]> message) {
            log(LOG_LEVEL::ERROR, message.get());
        };

        void critical(char* message) {
            log(LOG_LEVEL::CRITICAL, message);
        };

        void critical(const char* message) {
            log(LOG_LEVEL::CRITICAL, message);
        };

        void critical(std::unique_ptr<char[]> message) {
            log(LOG_LEVEL::CRITICAL, message.get());
        };
    };
}
