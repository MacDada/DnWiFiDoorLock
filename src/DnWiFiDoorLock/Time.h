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

        unsigned long getMilliseconds() const;

        long getSeconds() const;

        long getMinutes() const;

        int getHours() const;

        byte getDays() const;

        int getRemainingMilliseconds() const;

        byte getRemainingSeconds() const;

        byte getRemainingMinutes() const;

        byte getRemainingHours() const;
    };

}
