#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Hardware/Led.h"

namespace DnApp::Hardware {
    class InMemoryLed final:
        public DnApp::Hardware::Led {
    public:
        auto isOn() const -> bool override {
            return _on;
        }

        auto isOff() const -> bool override {
            return !_on;
        };

        auto on() -> void override {
            _on = true;
        };

        auto off() -> void override {
            _on = false;
        };

        auto toggle() -> void override {
            _on = !_on;
        };
    private:
        bool _on = false;
    };

    static_assert(!std::is_abstract<InMemoryLed>());
}
