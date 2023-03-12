#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Hardware/DigitalPin.h"
#include "DnApp/Hardware/Led.h"

namespace DnApp::Hardware {
    class LedOnDigitalPin final:
        public DnApp::Hardware::Led {
    public:
        explicit
        LedOnDigitalPin(DnApp::Hardware::DigitalPin& pin) noexcept:
            pin{pin} {
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
        DnApp::Hardware::DigitalPin& pin;
    };

    static_assert(!std::is_abstract<LedOnDigitalPin>());
}
