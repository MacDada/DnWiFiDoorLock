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

        bool isOn();

        bool isOff();

        void toggle();
    };

}
