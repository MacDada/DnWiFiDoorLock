#pragma once

#include <cstdint>     // uint16_t
#include <type_traits> // std::is_abstract

#include "DnApp/Hardware/Button.h"

namespace DnApp::Hardware {
    class InMemoryButton final:
        public DnApp::Hardware::Button {
    public:
        auto press() -> void override {
            ++pressCount;
        }

        [[nodiscard]]
        auto getPressCount() const -> uint16_t {
            return pressCount;
        }

        auto resetPressCount() -> void {
            pressCount = 0;
        }

    private:
        uint16_t pressCount = 0;
    };

    static_assert(!std::is_abstract<InMemoryButton>());
}
