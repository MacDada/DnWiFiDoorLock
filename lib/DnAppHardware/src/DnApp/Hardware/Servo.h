#pragma once

#include <cstdint> // uint8_t
#include <optional>

namespace DnApp::Hardware {
    class Servo {
    public:
        class Angle final {
        public:
            static
            const auto MIN = uint8_t{0};

            static
            const auto MAX = uint8_t{180};

            static
            auto withDegrees(const uint8_t degrees) -> std::optional<Angle> {
                if (degrees < MIN || degrees > MAX) {
                    return {};
                }

                return Angle{degrees};
            }

            [[nodiscard]]
            auto getDegrees() const -> uint8_t {
                return degrees;
            }

            auto operator ==(const Angle& other) const -> bool {
                return degrees == other.degrees;
            }
        private:
            explicit
            Angle(const uint8_t degrees):
                degrees{degrees} {
            }

            uint8_t degrees;
        };

        [[nodiscard]]
        virtual
        auto getAngle() const -> Angle = 0;

        virtual
        auto setAngle(Angle angle) -> void = 0;
    };
}
