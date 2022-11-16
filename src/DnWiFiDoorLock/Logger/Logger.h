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

        virtual void log(LOG_LEVEL level, std::unique_ptr<char[]> message) = 0;

        virtual void log(LOG_LEVEL level, const char *message) = 0;

        virtual void log(LOG_LEVEL level, char *message) = 0;
    };

}
