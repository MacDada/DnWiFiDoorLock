#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Hardware/DigitalPin.h"

namespace DnApp::Hardware {
    class InMemoryDigitalPin final:
        public DnApp::Hardware::DigitalPin {
    public:
        [[nodiscard]]
        auto isOutputMode() const -> bool {
            return !inputMode;
        }

        [[nodiscard]]
        auto isInputMode() const -> bool {
            return inputMode;
        }

        auto setOutputMode() -> void override {
            inputMode = false;
        }

        auto setInputMode() -> void override {
            inputMode = true;
        }

        auto setHigh() -> void override {
            low = false;
        }

        auto setLow() -> void override {
            low = true;
        }

        [[nodiscard]]
        auto isHigh() const -> bool override {
            return !low;
        }

        [[nodiscard]]
        auto isLow() const -> bool override {
            return low;
        }
    private:
        bool inputMode = true;

        bool low = true;
    };

    static_assert(!std::is_abstract<InMemoryDigitalPin>());
}
