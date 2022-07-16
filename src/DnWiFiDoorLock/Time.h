#pragma once

#include <Arduino.h>

namespace DnWiFiDoorLock {

    class Time final {
    private:
        // todo: unify declarations order style across classes
        unsigned long milliseconds;
        long seconds;
        long minutes;
        int hours;
        byte days;

    public:
        static Time uptime();

        Time(const unsigned long milliseconds);

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
