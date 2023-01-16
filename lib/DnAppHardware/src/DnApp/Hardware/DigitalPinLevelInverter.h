#pragma once

#include <type_traits>

#include "DnApp/Hardware/DigitalPin.h"

namespace DnApp::Hardware {
    class DigitalPinLevelInverter final:
        public DnApp::Hardware::DigitalPin {
    public:
        explicit
        DigitalPinLevelInverter(DigitalPin& pin) noexcept:
            pin{pin} {
        }

        void setOutputMode() override {
            pin.setOutputMode();
        }

        void setInputMode() override {
            pin.setInputMode();
        }

        void setHigh() override {
            pin.setLow();
        }

        void setLow() override {
            pin.setHigh();
        }

        bool isHigh() const override {
            return pin.isLow();
        }

        bool isLow() const override {
            return pin.isHigh();
        }
    private:
        DigitalPin& pin;
    };

    static_assert(!std::is_abstract<DigitalPinLevelInverter>());
}
