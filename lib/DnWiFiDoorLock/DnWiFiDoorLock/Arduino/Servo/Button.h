#pragma once

#include <type_traits>

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
        void press() override {
            servo.setAngle(pressingAngle);

            scheduleStopPressing();
        }

        byte getPressingAngle() const {
            return pressingAngle;
        }

        void setPressingAngle(const byte angle) {
            this->pressingAngle = angle;
        }

        byte getNotPressingAngle() const {
            return notPressingAngle;
        }

        // todo: validation with VO?
        //       the VO could be created with std::variant
        //       or even better, with std::expected
        //       https://mariusbancila.ro/blog/2022/08/17/using-the-cpp23-expected-type/
        void setNotPressingAngle(const byte angle) {
            this->notPressingAngle = angle;
        }

        int getPressingMilliseconds() const {
            return pressingMilliseconds;
        }

        void setPressingMilliseconds(const int milliseconds) {
            this->pressingMilliseconds = milliseconds;
        }

        void onSetup() override {
            // just in case the servo is in the pressing position at the start
            stopPressing();
        };

        void onLoop() override {
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

        void scheduleStopPressing() {
            stopPressingAtUptimeMilliseconds = getUptimeMilliseconds() + pressingMilliseconds;
        }

        bool isItTimeToStopPressing() const {
            return stopPressingAtUptimeMilliseconds
                && getUptimeMilliseconds() > stopPressingAtUptimeMilliseconds;
        }

        unsigned long getUptimeMilliseconds() const {
            return hardware.getUptime().getMilliseconds();
        }

        void stopPressing() {
            servo.setAngle(notPressingAngle);

            stopPressingAtUptimeMilliseconds = 0;
        }
    };

    static_assert(!std::is_abstract<Button>());
}
