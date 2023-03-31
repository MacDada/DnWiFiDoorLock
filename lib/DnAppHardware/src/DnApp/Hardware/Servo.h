#pragma once

namespace DnApp::Hardware {
    class Servo {
    public:
        static const int MIN_ANGLE = 0;

        static const int MAX_ANGLE = 180;

        virtual
        auto getAngle() const -> int = 0;

        virtual
        auto setAngle(int degrees) -> void = 0;
    };
}
