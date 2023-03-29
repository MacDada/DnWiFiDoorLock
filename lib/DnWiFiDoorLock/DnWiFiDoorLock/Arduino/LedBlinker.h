#pragma once

#include <Arduino.h>

#include "DnApp/Hardware/Led.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"

namespace DnWiFiDoorLock::Arduino {
    class LedBlinker final {
    public:
        explicit
        LedBlinker(
            DnWiFiDoorLock::Arduino::Hardware& hardware,
            DnApp::Hardware::Led& led
        ):
            hardware{hardware},
            led{led} {
        }

        auto blinkFast(const int count) -> void {
            for (auto i = decltype(count){0}; i < count; ++i) {
                led.on();
                hardware.pause(100);
                led.off();
                hardware.pause(100);
            }
        }
    private:
        DnWiFiDoorLock::Arduino::Hardware& hardware;

        DnApp::Hardware::Led& led;
    };
}
