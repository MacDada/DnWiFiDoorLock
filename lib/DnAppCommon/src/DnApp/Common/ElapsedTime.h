#pragma once

#include <cstdint> // uint32_t, uint16_t, uint8_t

namespace DnApp::Common {
    class ElapsedTime final {
    private:
        const uint32_t milliseconds;

        const uint32_t seconds;

        const uint32_t minutes;

        const uint16_t hours;

        const uint8_t days;
    public:
        // Accepting `uint32_t` as this is a 32–bit value.
        //
        // No point in making it bigger,
        // as this is primarily used to present the microcontroller's uptime,
        // and Arduino's `millis()` is returning `unsigned long`,
        // which on ESP8266 is a 32–bit value (see `README.md`).
        //
        // That gives us max ~49 days without restart xD
        // 4294967295/1000/60/60/24 = ~49
        //
        // todo:[1] What will happen after 49 days?
        //       A crash? Or `millis()` will just give a wrong result?
        //       -> probably strange behaviour from type size overflows
        //       -> Maybe I should just force restart when overflow actually occurs?
        explicit
        ElapsedTime(const uint32_t milliseconds):
            milliseconds{milliseconds},
            seconds{milliseconds / 1000},
            minutes{seconds / 60},
            hours(minutes / 60),
            days(hours / 24) {
            // potential RAM saving:
            //   calculate on demand,
            //   instead of storing precalculated values,
            //   4 bytes each ;-)
        }

        auto getMilliseconds() const -> uint32_t {
            return milliseconds;
        }

        auto getSeconds() const -> uint32_t {
            return seconds;
        }

        auto getMinutes() const -> uint32_t {
            return minutes;
        }

        auto getHours() const -> uint16_t {
            return hours;
        }

        auto getDays() const -> uint8_t {
            return days;
        }

        auto getRemainingMilliseconds() const -> uint16_t {
            return milliseconds % 1000;
        }

        auto getRemainingSeconds() const -> uint8_t {
            return seconds % 60;
        }

        auto getRemainingMinutes() const -> uint8_t {
            return minutes % 60;
        }

        auto getRemainingHours() const -> uint8_t {
            return hours % 24;
        }
    };
}
