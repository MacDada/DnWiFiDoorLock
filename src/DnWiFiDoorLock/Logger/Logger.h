#pragma once

#include <memory>

/**
 * todo: log levels
 */

namespace DnWiFiDoorLock::Logger {

    class Logger {
    public:
        virtual void log(std::unique_ptr<char[]> message) = 0;

        virtual void log(const char *message) = 0;

        virtual void log(char *message) = 0;
    };

}
