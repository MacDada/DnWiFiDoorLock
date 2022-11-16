#pragma once

#include <memory>

namespace DnWiFiDoorLock::Logger {

    class Logger {
    public:
        enum struct LOG_LEVEL {
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            CRITICAL
        };

        static constexpr const char *LOG_LEVELS[] = {
            "debug",
            "info",
            "warning",
            "error",
            "critical"
        };

        // ATTENTION!
        // https://isocpp.org/wiki/faq/strange-inheritance#hiding-rule
        void log(LOG_LEVEL level, std::unique_ptr<char[]> message) {
            log(level, message.get());
        }

        virtual void log(LOG_LEVEL level, const char *message) = 0;

        virtual void log(LOG_LEVEL level, char *message) = 0;

        void debug(std::unique_ptr<char[]> message) {
            log(LOG_LEVEL::DEBUG, message.get());
        };

        void debug(const char *message) {
            log(LOG_LEVEL::DEBUG, message);
        };

        void debug(char *message) {
            log(LOG_LEVEL::DEBUG, message);
        };

        void info(std::unique_ptr<char[]> message) {
            log(LOG_LEVEL::INFO, message.get());
        };

        void info(const char *message) {
            log(LOG_LEVEL::INFO, message);
        };

        void info(char *message) {
            log(LOG_LEVEL::INFO, message);
        };

        void warning(std::unique_ptr<char[]> message) {
            log(LOG_LEVEL::WARNING, message.get());
        };

        void warning(const char *message) {
            log(LOG_LEVEL::WARNING, message);
        };

        void warning(char *message) {
            log(LOG_LEVEL::WARNING, message);
        };

        void error(std::unique_ptr<char[]> message) {
            log(LOG_LEVEL::ERROR, message.get());
        };

        void error(const char *message) {
            log(LOG_LEVEL::ERROR, message);
        };

        void error(char *message) {
            log(LOG_LEVEL::ERROR, message);
        };

        void critical(std::unique_ptr<char[]> message) {
            log(LOG_LEVEL::CRITICAL, message.get());
        };

        void critical(const char *message) {
            log(LOG_LEVEL::CRITICAL, message);
        };

        void critical(char *message) {
            log(LOG_LEVEL::CRITICAL, message);
        };
    };

}
