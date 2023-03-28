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

        auto isOn() const -> bool override {
            return pin.isHigh();
        }

        auto isOff() const -> bool override {
            return pin.isLow();
        };

        auto on() -> void override {
            pin.setHigh();
        };

        auto off() -> void override {
            pin.setLow();
        };

        auto toggle() -> void override {
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
