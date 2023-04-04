#pragma once

#include <Arduino.h>

namespace DnApp::Common {
    class ElapsedTime final {
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
        // what will happen after 49 days?
        // a crash? or `millis()` will just give a wrong result?
        explicit
        ElapsedTime(const unsigned long milliseconds):
            milliseconds{milliseconds},
            seconds(milliseconds / 1000),
            minutes{seconds / 60},
            hours(minutes / 60),
            days(hours / 24) {
            // potential RAM saving:
            //   calculate on demand,
            //   instead of storing precalculated values,
            //   4 bytes each ;-)
        }

        auto getMilliseconds() const -> unsigned long {
            return milliseconds;
        }

        auto getSeconds() const -> long {
            return seconds;
        }

        auto getMinutes() const -> long {
            return minutes;
        }

        auto getHours() const -> int {
            return hours;
        }

        // `byte` is enough, we won't be going longer than 49 days xD
        auto getDays() const -> byte {
            return days;
        }

        auto getRemainingMilliseconds() const -> int {
            return milliseconds % 1000;
        }

        auto getRemainingSeconds() const -> byte {
            return seconds % 60;
        }

        auto getRemainingMinutes() const -> byte {
            return minutes % 60;
        }

        auto getRemainingHours() const -> byte {
            return hours % 24;
        }
    };
}
