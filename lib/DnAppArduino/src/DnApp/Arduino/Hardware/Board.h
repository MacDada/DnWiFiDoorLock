#pragma once

#include <Arduino.h>

#include "DnApp/Common/Duration.h"

namespace DnApp::Arduino::Hardware {
    class Board final {
    public:
        static
        const auto BUILT_IN_LED_PIN = LED_BUILTIN;

        auto pause(const unsigned long milliseconds) -> void {
            delay(milliseconds);
        }

        [[nodiscard]]
        auto getUptime() const -> DnApp::Common::Duration {
            return DnApp::Common::Duration{millis()};
        }
    };
}
