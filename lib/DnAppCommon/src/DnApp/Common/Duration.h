#pragma once

#include <cstdint> // uint32_t, uint16_t, uint8_t

namespace DnApp::Common {
    class Duration final {
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
        Duration(const uint32_t milliseconds):
            milliseconds{milliseconds} {
        }

        [[nodiscard]]
        auto getMilliseconds() const -> uint32_t {
            return milliseconds;
        }

        [[nodiscard]]
        auto getSeconds() const -> uint32_t {
            return milliseconds / 1000;
        }

        [[nodiscard]]
        auto getMinutes() const -> uint32_t {
            return getSeconds() / 60;
        }

        [[nodiscard]]
        auto getHours() const -> uint16_t {
            return getMinutes() / 60;
        }

        [[nodiscard]]
        auto getDays() const -> uint8_t {
            return getHours() / 24;
        }

        [[nodiscard]]
        auto getMillisecondsRemainder() const -> uint16_t {
            return milliseconds % 1000;
        }

        [[nodiscard]]
        auto getSecondsRemainder() const -> uint8_t {
            return getSeconds() % 60;
        }

        [[nodiscard]]
        auto getMinutesRemainder() const -> uint8_t {
            return getMinutes() % 60;
        }

        [[nodiscard]]
        auto getHoursRemainder() const -> uint8_t {
            return getHours() % 24;
        }
    private:
        const uint32_t milliseconds;
    };
}
