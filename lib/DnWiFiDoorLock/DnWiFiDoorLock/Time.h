#pragma once

#include <Arduino.h>

namespace DnWiFiDoorLock {
    class Time final {
    private:
        const unsigned long milliseconds;

        const long seconds;

        const long minutes;

        const int hours;

        const byte days;
    public:
        // If I count correctly, `unsigned long` gives us max 49 days without restart xD
        // 4294967295/1000/60/60/24 ~= 49
        //
        // btw, I used to have `int` here:
        // how is that the compiler did not warn me
        // that the potential value coming here could me `unsigned long`,
        // which is given by `millis()`?
        // what will happen after 49 days?
        // a crash? or `millis()` will just give a wrong result?
        explicit
        Time(const unsigned long milliseconds):
            milliseconds(milliseconds),
            seconds(milliseconds / 1000),
            minutes(seconds / 60),
            hours(minutes / 60),
            days(hours / 24) {
            // potential RAM saving:
            //   calculate on demand,
            //   instead of storing precalculated values,
            //   4 bytes each ;-)
        }

        unsigned long getMilliseconds() const {
            return milliseconds;
        }

        long getSeconds() const {
            return seconds;
        }

        long getMinutes() const {
            return minutes;
        }

        int getHours() const {
            return hours;
        }

        // `byte` is enough, we won't be going longer than 49 days xD
        byte getDays() const {
            return days;
        }

        int getRemainingMilliseconds() const {
            return milliseconds % 1000;
        }

        byte getRemainingSeconds() const {
            return seconds % 60;
        }

        byte getRemainingMinutes() const {
            return minutes % 60;
        }

        byte getRemainingHours() const {
            return hours % 24;
        }
    };
}
