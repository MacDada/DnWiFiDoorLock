#pragma once

#include <Arduino.h>

namespace DnWiFiDoorLock {
    class DnTime {
    private:
        unsigned long milliseconds;
        long seconds;
        long minutes;
        int hours;
        byte days;

    public:
        static DnTime uptime();

        DnTime(const unsigned long milliseconds);

        unsigned long getMilliseconds();

        long getSeconds();

        long getMinutes();

        int getHours();

        byte getDays();

        int getRemainingMilliseconds();

        byte getRemainingSeconds();

        byte getRemainingMinutes();

        byte getRemainingHours();
    };
}
