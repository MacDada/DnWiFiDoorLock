#pragma once

#include <Arduino.h>

#include "DnWiFiDoorLock/Arduino/Hardware.h"

namespace DnWiFiDoorLock::Arduino {

    class Led final {
    private:
        DnWiFiDoorLock::Arduino::Hardware &hardware;
        byte pin;

    public:
        Led(DnWiFiDoorLock::Arduino::Hardware &hardware, const byte pin);

        void on();

        void off();

        void blinkFast(const int count);

        bool isOn();

        bool isOff();

        void toggle();
    };

}
