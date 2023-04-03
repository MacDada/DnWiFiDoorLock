#pragma once

#include <type_traits> // std::is_abstract

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
    public:
        explicit
        Button(
            const DnApp::Arduino::Hardware::Board& board,
            Servo& servo,
            const Servo::Angle pressingAngle,
            const Servo::Angle notPressingAngle,
            const int pressingMilliseconds
        ):
            board{board},
            servo{servo},
            pressingAngle{pressingAngle},
            notPressingAngle{notPressingAngle},
            pressingMilliseconds{pressingMilliseconds} {
        }

        // pressing the button, while it is being pressed,
        // will prolong the pressing
        auto press() -> void override {
            servo.setAngle(pressingAngle);

            scheduleStopPressing();
        }

        auto getPressingAngle() const -> Servo::Angle {
            return pressingAngle;
        }

        auto setPressingAngle(const Servo::Angle angle) -> void {
            pressingAngle = angle;
        }

        auto getNotPressingAngle() const -> Servo::Angle {
            return notPressingAngle;
        }

        // todo: the VO could be created with std::expected
        //       https://mariusbancila.ro/blog/2022/08/17/using-the-cpp23-expected-type/
        auto setNotPressingAngle(const Servo::Angle angle) -> void {
            notPressingAngle = angle;
        }

        auto getPressingMilliseconds() const -> int {
            return pressingMilliseconds;
        }

        auto setPressingMilliseconds(const int milliseconds) -> void {
            this->pressingMilliseconds = milliseconds;
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
    private:
        const DnApp::Arduino::Hardware::Board& board;

        Servo& servo;

        Servo::Angle pressingAngle;

        Servo::Angle notPressingAngle;

        int pressingMilliseconds;

        unsigned long stopPressingAtUptimeMilliseconds = 0;

        auto scheduleStopPressing() -> void {
            stopPressingAtUptimeMilliseconds = getUptimeMilliseconds() + pressingMilliseconds;
        }

        auto isItTimeToStopPressing() const -> bool {
            return stopPressingAtUptimeMilliseconds
                && getUptimeMilliseconds() > stopPressingAtUptimeMilliseconds;
        }

        auto getUptimeMilliseconds() const -> unsigned long {
            return board.getUptime().getMilliseconds();
        }

        auto stopPressing() -> void {
            servo.setAngle(notPressingAngle);

            stopPressingAtUptimeMilliseconds = 0;
        }
    };

    static_assert(!std::is_abstract<Button>());
}
