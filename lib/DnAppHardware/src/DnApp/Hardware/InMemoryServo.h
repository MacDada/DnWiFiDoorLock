#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Hardware/Servo.h"

namespace DnApp::Hardware {
    class InMemoryServo final:
        public DnApp::Hardware::Servo {
    public:
        auto getAngle() const -> int override {
            return degrees;
        }

        auto setAngle(const int degrees) -> void override {
            this->degrees = degrees;
        }
    private:
        int degrees = 0;
    };

    static_assert(!std::is_abstract<InMemoryServo>());
}
