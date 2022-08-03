#pragma once

#include <Arduino.h>

namespace DnWiFiDoorLock {

    class Time final {
    private:
        // todo: unify declarations order style across classes
        const unsigned long milliseconds;

        const long seconds;

        const long minutes;

        const int hours;

        const byte days;

    public:
        explicit Time(unsigned long milliseconds);

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
