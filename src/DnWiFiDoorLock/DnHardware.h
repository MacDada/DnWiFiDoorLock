#pragma once

#include <Arduino.h>

#include "DnTime.h"

namespace DnWiFiDoorLock {
    class DnHardware {
    public:
        static const byte BUILT_IN_LED_PIN = LED_BUILTIN;

        DnTime getUptime();

        void setPinToOutputMode(const byte pin);

        void digitalWriteHigh(const byte pin);

        void digitalWriteLow(const byte pin);

        void startSerial(const long bitsPerSecond);
    };
}
