#include "Time.h"

namespace DnWiFiDoorLock {

    Time Time::uptime() {
        return Time(millis());
    }

    // If I count correctly, `unsigned long` gives us max 49 days without restart xD
    // 4294967295/1000/60/60/24 ~= 49
    //
    // btw, i used to have `int` here:
    // how is that the compiler did not warn me
    // that the potencial value coming here could me `unsigned long`,
    // which is given by `millis()`?
    // what will happen after 49 days?
    // a crash? or `millis()` will just give a wrong result?
    //
    // another question: does static `const` for arg make any difference?
    Time::Time(const unsigned long milliseconds) {
        // potential RAM saving:
        //   calculate on demand,
        //   instead of storing precalculated values,
        //   4 bytes each ;-)
        this->milliseconds = milliseconds;
        seconds = milliseconds / 1000;
        minutes = seconds / 60;
        hours = minutes / 60;
        days = hours / 24;
    }

    unsigned long Time::getMilliseconds() {
        return milliseconds;
    }

    long Time::getSeconds() {
        return seconds;
    }

    long Time::getMinutes() {
        return minutes;
    }

    int Time::getHours() {
        return hours;
    }

    // `byte` is enough, we won't be going longer than 49 days xD
    byte Time::getDays() {
        return days;
    }

    int Time::getRemainingMilliseconds() {
        return milliseconds % 1000;
    }

    byte Time::getRemainingSeconds() {
        return seconds % 60;
    }

    byte Time::getRemainingMinutes() {
        return minutes % 60;
    }

    byte Time::getRemainingHours() {
        return hours % 24;
    }

}
