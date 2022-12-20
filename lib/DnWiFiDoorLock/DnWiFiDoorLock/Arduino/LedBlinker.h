#pragma once

#include <Arduino.h>

#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/Led.h"

namespace DnWiFiDoorLock::Arduino {
    class LedBlinker final {
    public:
        LedBlinker(
            const DnWiFiDoorLock::Arduino::Hardware &hardware,
            const Led &led
        );

        void blinkFast(int count) const;
    private:
        const DnWiFiDoorLock::Arduino::Hardware &hardware;

        const DnWiFiDoorLock::Arduino::Led &led;
    };
}
