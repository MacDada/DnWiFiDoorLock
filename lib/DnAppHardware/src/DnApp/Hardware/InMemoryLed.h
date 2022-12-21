#pragma once

#include <type_traits>

#include "DnApp/Hardware/Led.h"

namespace DnApp::Hardware {
    class InMemoryLed final:
        public DnApp::Hardware::Led {
    public:
        bool isOn() const override {
            return _on;
        }

        bool isOff() const override {
            return !_on;
        };

        void on() override {
            _on = true;
        };

        void off() override {
            _on = false;
        };

        void toggle() override {
            _on = !_on;
        };
    private:
        bool _on = false;
    };

    static_assert(!std::is_abstract<InMemoryLed>());
}
