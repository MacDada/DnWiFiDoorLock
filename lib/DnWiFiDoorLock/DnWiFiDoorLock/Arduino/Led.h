#pragma once

#include <Arduino.h>

#include "DnApp/Arduino/Hardware/DigitalPin.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"

namespace DnWiFiDoorLock::Arduino {
    class Led final {
    public:
        explicit
        Led(byte pinId): pinId(pinId), pin(pinId) {
            pin.setOutputMode();
        }

        bool isOn() const {
            if (BUILT_IN_LED_PIN_ID == pinId) {
                return pin.isLow();
            } else {
                return pin.isHigh();
            }
        };

        bool isOff() const {
            if (BUILT_IN_LED_PIN_ID == pinId) {
                return pin.isHigh();
            } else {
                return pin.isLow();
            }
        };

        void on() const {
            // it is inverted for built–in led => so it should be high for normal led
            // https://github.com/nodemcu/nodemcu-devkit-v1.0/issues/16
            // https://stackoverflow.com/questions/46087828/why-is-nodemcu-triggering-gpio-in-reverse-when-using-lua
            if (BUILT_IN_LED_PIN_ID == pinId) {
                pin.setLow();
            } else {
                pin.setHigh();
            }
        };

        void off() const {
            if (BUILT_IN_LED_PIN_ID == pinId) {
                pin.setHigh();
            } else {
                pin.setLow();
            }
        };

        void toggle() const {
            if (isOn()) {
                off();
            } else {
                on();
            }
        };
    private:
        static
        constexpr
        const byte BUILT_IN_LED_PIN_ID = DnWiFiDoorLock::Arduino::Hardware::BUILT_IN_LED_PIN;

        const byte pinId;

        DnApp::Arduino::Hardware::DigitalPin pin;
    };
}
