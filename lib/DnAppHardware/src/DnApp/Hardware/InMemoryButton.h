#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Hardware/Button.h"

namespace DnApp::Hardware {
    class InMemoryButton final:
        public DnApp::Hardware::Button {
    public:
        void press() override {
            ++pressCount;
        }

        int getPressCount() const {
            return pressCount;
        }

        void resetPressCount() {
            pressCount = 0;
        }

    private:
        int pressCount = 0;
    };

    static_assert(!std::is_abstract<InMemoryButton>());
}
