#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Hardware/Led.h"

namespace DnApp::Hardware {
    class LedInverter final:
        public DnApp::Hardware::Led {
    public:
        explicit
        LedInverter(Led& led) noexcept:
            led{led} {
        }

        auto isOn() const -> bool override {
            return led.isOff();
        }

        auto isOff() const -> bool override {
            return led.isOn();
        };

        auto on() -> void override {
            led.off();
        };

        auto off() -> void override {
            led.on();
        };

        auto toggle() -> void override {
            led.toggle();
        };
    private:
        Led& led;
    };

    static_assert(!std::is_abstract<LedInverter>());
}
