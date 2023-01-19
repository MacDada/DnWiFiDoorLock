#pragma once

#include <Arduino.h>

#include "DnApp/Hardware/Led.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"

namespace DnWiFiDoorLock::Arduino {
    class LedBlinker final {
    public:
        explicit
        LedBlinker(
            const DnWiFiDoorLock::Arduino::Hardware& hardware,
            DnApp::Hardware::Led& led
        ):
            hardware{hardware},
            led{led} {
        }

        void blinkFast(const int count) {
            for (int i = 0; i < count; ++i) {
                led.on();
                hardware.pause(100);
                led.off();
                hardware.pause(100);
            }
        }
    private:
        const DnWiFiDoorLock::Arduino::Hardware& hardware;

        DnApp::Hardware::Led& led;
    };
}
