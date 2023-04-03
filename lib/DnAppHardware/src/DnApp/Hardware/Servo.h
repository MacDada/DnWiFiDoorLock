#pragma once

#include <optional>

namespace DnApp::Hardware {
    class Servo {
    public:
        class Angle final {
        public:
            static
            const int MIN = 0;

            static
            const int MAX = 180;

            static
            auto withDegrees(const int degrees) -> std::optional<Angle> {
                if (degrees < MIN || degrees > MAX) {
                    return {};
                }

                return Angle{degrees};
            }

            auto getDegrees() const -> int {
                return degrees;
            }
        private:
            explicit
            Angle(const int degrees):
                degrees{degrees} {
            }

            int degrees;
        };

        // todo: return Angle
        virtual
        auto getAngle() const -> int = 0;

        virtual
        auto setAngle(Angle angle) -> void = 0;
    };
}
