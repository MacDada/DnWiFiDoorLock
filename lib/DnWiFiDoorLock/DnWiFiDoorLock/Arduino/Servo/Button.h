#pragma once

#include <cstdint>     // uint32_t
#include <type_traits> // std::is_abstract

#include <WString.h>
#include <tl_expected>

#include "DnApp/Arduino/Hardware/Board.h"
#include "DnApp/Arduino/Kernel/SetupAndLoopAware.h"
#include "DnApp/Hardware/Button.h"
#include "DnApp/Hardware/Servo.h"

namespace DnWiFiDoorLock::Arduino::Servo {
    class Button final:
        public DnApp::Hardware::Button,
        public DnApp::Arduino::Kernel::SetupAndLoopAware {
    private:
        using Servo = DnApp::Hardware::Servo;
        using Board = DnApp::Arduino::Hardware::Board;
    public:
        class PressingMilliseconds final {
        public:
            static
            auto create(
                uint32_t value
            ) -> tl::expected<PressingMilliseconds, String> {
                if (value == 0) {
                    return tl::unexpected{PSTR("Positive integer required")};
                }

                return PressingMilliseconds{value};
            }

            auto getValue() const -> uint32_t {
                return value;
            }
        private:
            explicit
            PressingMilliseconds(uint32_t value):
                value{value} {
            }

            uint32_t value;
        };

        struct Settings final {
            Servo::Angle pressingAngle;

            Servo::Angle notPressingAngle;

            PressingMilliseconds pressingMilliseconds;
        };

        explicit
        Button(
            const Settings settings,
            const Board& board,
            Servo& servo
        ):
            settings{settings},
            board{board},
            servo{servo} {
        }

        // pressing the button, while it is being pressed,
        // will prolong the pressing
        auto press() -> void override {
            servo.setAngle(settings.pressingAngle);

            scheduleStopPressing();
        }

        auto onSetup() -> void override {
            // just in case the servo is in the pressing position at the start
            stopPressing();
        };

        auto onLoop() -> void override {
            if (isItTimeToStopPressing()) {
                stopPressing();
            }
        }

        Settings settings;
    private:
        const Board& board;

        Servo& servo;

        uint32_t stopPressingAtUptimeMilliseconds = 0;

        auto scheduleStopPressing() -> void {
            // todo:[1] possible uint32_t overflow
            stopPressingAtUptimeMilliseconds = getUptimeMilliseconds()
                + settings.pressingMilliseconds.getValue();
        }

        auto isItTimeToStopPressing() const -> bool {
            return stopPressingAtUptimeMilliseconds
                && getUptimeMilliseconds() > stopPressingAtUptimeMilliseconds;
        }

        auto getUptimeMilliseconds() const -> uint32_t {
            return board.getUptime().getMilliseconds();
        }

        auto stopPressing() -> void {
            servo.setAngle(settings.notPressingAngle);

            stopPressingAtUptimeMilliseconds = 0;
        }
    };

    static_assert(!std::is_abstract<Button>());
}
