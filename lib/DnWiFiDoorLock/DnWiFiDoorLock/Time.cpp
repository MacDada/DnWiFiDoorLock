#include "Time.h"

namespace DnWiFiDoorLock {

    // If I count correctly, `unsigned long` gives us max 49 days without restart xD
    // 4294967295/1000/60/60/24 ~= 49
    //
    // btw, I used to have `int` here:
    // how is that the compiler did not warn me
    // that the potential value coming here could me `unsigned long`,
    // which is given by `millis()`?
    // what will happen after 49 days?
    // a crash? or `millis()` will just give a wrong result?
    Time::Time(const unsigned long milliseconds):
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

    unsigned long Time::getMilliseconds() const {
        return milliseconds;
    }

    long Time::getSeconds() const {
        return seconds;
    }

    long Time::getMinutes() const {
        return minutes;
    }

    int Time::getHours() const {
        return hours;
    }

    // `byte` is enough, we won't be going longer than 49 days xD
    byte Time::getDays() const {
        return days;
    }

    int Time::getRemainingMilliseconds() const {
        return milliseconds % 1000;
    }

    byte Time::getRemainingSeconds() const {
        return seconds % 60;
    }

    byte Time::getRemainingMinutes() const {
        return minutes % 60;
    }

    byte Time::getRemainingHours() const {
        return hours % 24;
    }

}
