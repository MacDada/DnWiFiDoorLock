#pragma once

#include <type_traits>

#include "DnApp/Hardware/DigitalPin.h"
#include "DnApp/Hardware/Led.h"

namespace DnWiFiDoorLock::Arduino {
    class Led final:
        public DnApp::Hardware::Led {
    public:
        explicit
        Led(DnApp::Hardware::DigitalPin &pin): pin(pin) {
            pin.setOutputMode();
        }

        bool isOn() const override {
            return pin.isHigh();
        }

        bool isOff() const override {
            return pin.isLow();
        };

        void on() override {
            pin.setHigh();
        };

        void off() override {
            pin.setLow();
        };

        void toggle() override {
            if (isOn()) {
                off();
            } else {
                on();
            }
        };
    private:
        DnApp::Hardware::DigitalPin &pin;
    };

    static_assert(!std::is_abstract<Led>());
}
