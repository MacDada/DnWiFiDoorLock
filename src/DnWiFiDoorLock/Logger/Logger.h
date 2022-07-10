#pragma once

/**
 * todo: log levels
 */

namespace DnWiFiDoorLock::Logger {

    class Logger {
    public:
        virtual void log(const char *m) = 0;

        virtual void log(char *m) = 0;

        virtual void log(int m) = 0;

        virtual void log(double m) = 0;

        virtual void log(float m) = 0;
    };

}
