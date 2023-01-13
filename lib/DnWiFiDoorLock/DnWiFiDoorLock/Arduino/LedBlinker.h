#pragma once

#include <Arduino.h>

#include "DnApp/Hardware/Led.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"

namespace DnWiFiDoorLock::Arduino {
    class LedBlinker final {
    public:
        LedBlinker(
            const DnWiFiDoorLock::Arduino::Hardware& hardware,
            DnApp::Hardware::Led& led
        );

        void blinkFast(int count);
    private:
        const DnWiFiDoorLock::Arduino::Hardware& hardware;

        DnApp::Hardware::Led& led;
    };
}
