#pragma once

#include <type_traits>

#include "DnApp/Hardware/DigitalPin.h"

namespace DnApp::Hardware {
    class InMemoryDigitalPin final:
        public DnApp::Hardware::DigitalPin {
    public:
        bool isOutputMode() const {
            return !inputMode;
        }

        bool isInputMode() const {
            return inputMode;
        }

        void setOutputMode() override {
            inputMode = false;
        }

        void setInputMode() override {
            inputMode = true;
        }

        void setHigh() override {
            low = false;
        }

        void setLow() override {
            low = true;
        }

        bool isHigh() const override {
            return !low;
        }

        bool isLow() const override {
            return low;
        }
    private:
        bool inputMode = true;

        bool low = true;
    };

    static_assert(!std::is_abstract<InMemoryDigitalPin>());
}
