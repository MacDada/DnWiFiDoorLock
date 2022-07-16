#pragma once

#include <Arduino.h>

#include "Time.h"

namespace DnWiFiDoorLock {

    class Hardware final {
    public:
        static const byte BUILT_IN_LED_PIN = LED_BUILTIN;

        void pause(const unsigned long milliseconds);

        Time getUptime();

        void setPinToOutputMode(const byte pin);

        void digitalWriteHigh(const byte pin);

        void digitalWriteLow(const byte pin);

        void startSerial(const long bitsPerSecond);
    };

}
