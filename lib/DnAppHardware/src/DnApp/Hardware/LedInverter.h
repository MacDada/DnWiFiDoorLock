#pragma once

#include <type_traits>

#include "DnApp/Hardware/Led.h"

namespace DnApp::Hardware {
    class LedInverter final:
        public DnApp::Hardware::Led {
    public:
        explicit
        LedInverter(Led &led) noexcept:
            led(led) {
        }

        bool isOn() const override {
            return led.isOff();
        }

        bool isOff() const override {
            return led.isOn();
        };

        void on() override {
            led.off();
        };

        void off() override {
            led.on();
        };

        void toggle() override {
            led.toggle();
        };
    private:
        Led &led;
    };

    static_assert(!std::is_abstract<LedInverter>());
}
