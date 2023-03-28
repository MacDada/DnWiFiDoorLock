#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Hardware/Button.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Servo {
    class Button final:
        public DnApp::Hardware::Button,
        public SetupAndLoopAware {
    public:
        explicit
        Button(
            const Hardware& hardware,
            Servo& servo,
            const byte pressingAngle,
            const byte notPressingAngle,
            const int pressingMilliseconds
        ):
            hardware{hardware},
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

        auto getPressingAngle() const -> byte {
            return pressingAngle;
        }

        auto setPressingAngle(const byte angle) -> void {
            this->pressingAngle = angle;
        }

        auto getNotPressingAngle() const -> byte {
            return notPressingAngle;
        }

        // todo: validation with VO?
        //       the VO could be created with std::variant
        //       or even better, with std::expected
        //       https://mariusbancila.ro/blog/2022/08/17/using-the-cpp23-expected-type/
        auto setNotPressingAngle(const byte angle) -> void {
            this->notPressingAngle = angle;
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
        const Hardware& hardware;

        Servo& servo;

        byte pressingAngle;

        byte notPressingAngle;

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
            return hardware.getUptime().getMilliseconds();
        }

        auto stopPressing() -> void {
            servo.setAngle(notPressingAngle);

            stopPressingAtUptimeMilliseconds = 0;
        }
    };

    static_assert(!std::is_abstract<Button>());
}
