#pragma once

#include <Arduino.h>
#include "Hardware.h"

namespace DnWiFiDoorLock {

    class Led final {
    private:
        Hardware &hardware;
        byte pin;

    public:
        Led(Hardware &hardware, const byte pin);

        void on();

        void off();

        void blinkFast(const int count);

        void blinkLong(const int count);

        void blinkShortAndPause();

        void blink1sPause1s();
    };

}
