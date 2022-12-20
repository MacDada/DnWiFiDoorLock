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

        void setPinToInputMode(byte pin) const;

        void setPinToOutputMode(byte pin) const;

        void digitalWriteHigh(byte pin) const;

        void digitalWriteLow(byte pin) const;

        bool isPinHigh(byte pin) const;

        bool isPinLow(byte pin) const;
    };
}
