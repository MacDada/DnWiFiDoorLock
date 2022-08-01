#pragma once

/**
 * todo: log levels
 */

namespace DnWiFiDoorLock::Logger {

    class Logger {
    public:
        virtual void log(const char *message) = 0;

        virtual void log(char *message) = 0;

        virtual void log(int message) = 0;

        virtual void log(double message) = 0;

        virtual void log(float message) = 0;
    };

}
