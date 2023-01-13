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
        explicit Button(
            const Hardware& hardware,
            Servo& servo,
            byte pressingAngle,
            byte notPressingAngle,
            int pressingMilliseconds
        );

        void press() override;

        byte getPressingAngle() const {
            return pressingAngle;
        }

        void setPressingAngle(byte angle) {
            this->pressingAngle = angle;
        }

        byte getNotPressingAngle() const {
            return notPressingAngle;
        }

        // todo: validation with VO? the VO could be created with std::variant
        void setNotPressingAngle(byte angle) {
            this->notPressingAngle = angle;
        }

        int getPressingMilliseconds() const {
            return pressingMilliseconds;
        }

        void setPressingMilliseconds(int milliseconds) {
            this->pressingMilliseconds = milliseconds;
        }

        void onSetup() override;

        void onLoop() override;
    private:
        const Hardware& hardware;

        Servo& servo;

        byte pressingAngle;

        byte notPressingAngle;

        int pressingMilliseconds;

        unsigned long stopPressingAtUptimeMilliseconds = 0;

        void scheduleStopPressing();

        bool isItTimeToStopPressing() const;

        unsigned long getUptimeMilliseconds() const;

        void stopPressing();
    };

    static_assert(!std::is_abstract<Button>());
}
