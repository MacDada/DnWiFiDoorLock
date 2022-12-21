#pragma once

#include <Arduino.h>

#include "DnWiFiDoorLock/Time.h"

namespace DnWiFiDoorLock::Arduino {
    class Hardware final {
    public:
        static
        const byte BUILT_IN_LED_PIN = LED_BUILTIN;

        void pause(unsigned long milliseconds) const;

        Time getUptime() const;
    };
}
