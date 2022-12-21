#pragma once

#include <type_traits>

#include <Arduino.h>

#include "DnApp/Arduino/Hardware/DigitalPin.h"
#include "DnApp/Hardware/Led.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"

namespace DnWiFiDoorLock::Arduino {
    class Led final:
        public DnApp::Hardware::Led {
    public:
        explicit
        Led(byte pinId): pin(pinId) {
            pin.setOutputMode();
        }

        bool isOn() const override {
            if (inverted) {
                return pin.isLow();
            } else {
                return pin.isHigh();
            }
        }

        bool isOff() const override {
            if (inverted) {
                return pin.isHigh();
            } else {
                return pin.isLow();
            }
        };

        void on() override {
            if (inverted) {
                pin.setLow();
            } else {
                pin.setHigh();
            }
        };

        void off() override {
            if (inverted) {
                pin.setHigh();
            } else {
                pin.setLow();
            }
        };

        void toggle() override {
            if (isOn()) {
                off();
            } else {
                on();
            }
        };
    private:
        DnApp::Arduino::Hardware::DigitalPin pin;

        // it is inverted for built–in led
        // https://github.com/nodemcu/nodemcu-devkit-v1.0/issues/16
        // https://stackoverflow.com/questions/46087828/why-is-nodemcu-triggering-gpio-in-reverse-when-using-lua
        const bool inverted = DnWiFiDoorLock::Arduino::Hardware::BUILT_IN_LED_PIN == pin.getId();
    };

    static_assert(!std::is_abstract<Led>());
}
