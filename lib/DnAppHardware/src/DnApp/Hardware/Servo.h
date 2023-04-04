#pragma once

#include <cstdint> // uint8_t
#include <optional>

namespace DnApp::Hardware {
    class Servo {
    public:
        class Angle final {
        public:
            static
            const uint8_t MIN = 0;

            static
            const uint8_t MAX = 180;

            static
            auto withDegrees(const uint8_t degrees) -> std::optional<Angle> {
                if (degrees < MIN || degrees > MAX) {
                    return {};
                }

                return Angle{degrees};
            }

            auto getDegrees() const -> uint8_t {
                return degrees;
            }
        private:
            explicit
            Angle(const uint8_t degrees):
                degrees{degrees} {
            }

            uint8_t degrees;
        };

        virtual
        auto getAngle() const -> Angle = 0;

        virtual
        auto setAngle(Angle angle) -> void = 0;
    };
}
