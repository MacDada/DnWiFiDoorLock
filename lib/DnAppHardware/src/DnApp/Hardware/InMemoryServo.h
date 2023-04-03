#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Hardware/Servo.h"

namespace DnApp::Hardware {
    class InMemoryServo final:
        public DnApp::Hardware::Servo {
    public:
        static
        const int DEFAULT_ANGLE_DEGREES = 0;

        auto getAngle() const -> Angle override {
            return angle;
        }

        auto setAngle(const Angle angle) -> void override {
            this->angle = angle;
        }
    private:
        Angle angle = Angle::withDegrees(DEFAULT_ANGLE_DEGREES).value();
    };

    static_assert(!std::is_abstract<InMemoryServo>());
}
