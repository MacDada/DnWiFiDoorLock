#pragma once

#include <Arduino.h>

#include "DnWiFiDoorLock/Arduino/Hardware.h"

namespace DnWiFiDoorLock::Arduino {

    class Led final {
    private:
        DnWiFiDoorLock::Arduino::Hardware &hardware;
        byte pin;

    public:
        Led(DnWiFiDoorLock::Arduino::Hardware &hardware, byte pin);

        void on() const;

        void off() const;

        void blinkFast(int count) const;

        bool isOn() const;

        bool isOff() const;

        void toggle() const;
    };

}
