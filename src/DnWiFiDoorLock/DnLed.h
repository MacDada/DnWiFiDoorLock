#pragma once

#include <Arduino.h>
#include "DnHardware.h"

namespace DnWiFiDoorLock {
    class DnLed final {
    private:
        DnHardware *hardware;
        byte pin;

    public:
        DnLed(DnHardware &hardware, const byte pin);

        void on();

        void off();

        void blinkFast(const int count);

        void blinkLong(const int count);

        void blinkShortAndPause();

        void blink1sPause1s();
    };
}
