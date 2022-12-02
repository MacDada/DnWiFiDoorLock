#pragma once

#include <type_traits>

#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Button.h"

namespace DnWiFiDoorLock::Arduino::Servo {

    class Button final:
        public DnWiFiDoorLock::Button,
        public SetupAndLoopAware {
    public:
        explicit Button(
            const Hardware &hardware,
            Servo &servo,
            byte pressingAngle,
            byte notPressingAngle,
            int pressingMilliseconds
        );

        void press() override;

        void onSetup() override;

        void onLoop() override;

    private:
        const Hardware &hardware;

        Servo &servo;

        const byte pressingAngle;

        const byte notPressingAngle;

        const int pressingMilliseconds;

        unsigned long stopPressingAtUptimeMilliseconds = 0;

        void scheduleStopPressing();

        bool isItTimeToStopPressing() const;

        unsigned long getUptimeMilliseconds() const;

        void stopPressing();
    };

    static_assert(!std::is_abstract<Button>());

}
