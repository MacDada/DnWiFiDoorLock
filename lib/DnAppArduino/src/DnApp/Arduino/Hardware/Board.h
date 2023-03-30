#pragma once

#include <Arduino.h>

#include "DnWiFiDoorLock/Time.h"

namespace DnApp::Arduino::Hardware {
    class Board final {
    public:
        static
        const auto BUILT_IN_LED_PIN = LED_BUILTIN;

        auto pause(const unsigned long milliseconds) -> void {
            delay(milliseconds);
        }

        auto getUptime() const -> DnWiFiDoorLock::Time {
            return DnWiFiDoorLock::Time(millis());
        }
    };
}
