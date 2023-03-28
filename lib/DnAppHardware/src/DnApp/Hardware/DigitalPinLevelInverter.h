#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Hardware/DigitalPin.h"

namespace DnApp::Hardware {
    class DigitalPinLevelInverter final:
        public DnApp::Hardware::DigitalPin {
    public:
        explicit
        DigitalPinLevelInverter(DigitalPin& pin) noexcept:
            pin{pin} {
        }

        auto setOutputMode() -> void override {
            pin.setOutputMode();
        }

        auto setInputMode() -> void override {
            pin.setInputMode();
        }

        auto setHigh() -> void override {
            pin.setLow();
        }

        auto setLow() -> void override {
            pin.setHigh();
        }

        auto isHigh() const -> bool override {
            return pin.isLow();
        }

        auto isLow() const -> bool override {
            return pin.isHigh();
        }
    private:
        DigitalPin& pin;
    };

    static_assert(!std::is_abstract<DigitalPinLevelInverter>());
}
