#include "DnWiFiDoorLock/Arduino/Servo/Button.h"

namespace DnWiFiDoorLock::Arduino::Servo {

    Button::Button(
        const Hardware &hardware,
        Servo &servo,
        const byte pressingAngle,
        const byte notPressingAngle,
        const int pressingMilliseconds
    ):
        hardware(hardware),
        servo(servo),
        pressingAngle(pressingAngle),
        notPressingAngle(notPressingAngle),
        pressingMilliseconds(pressingMilliseconds) {
    }

    // pressing the button, while it is being pressed,
    // will prolong the pressing
    void Button::press() {
        servo.setAngle(pressingAngle);

        scheduleStopPressing();
    }

    void Button::onSetup() {
        // just in case the servo is in the pressing position at the start
        stopPressing();
    };

    void Button::onLoop() {
        if (isItTimeToStopPressing()) {
            stopPressing();
        }
    }

    void Button::stopPressing() {
        servo.setAngle(notPressingAngle);

        stopPressingAtUptimeMilliseconds = 0;
    }

    void Button::scheduleStopPressing() {
        stopPressingAtUptimeMilliseconds = getUptimeMilliseconds() + pressingMilliseconds;
    }

    bool Button::isItTimeToStopPressing() const {
        return stopPressingAtUptimeMilliseconds
           && getUptimeMilliseconds() > stopPressingAtUptimeMilliseconds;
    }

    unsigned long Button::getUptimeMilliseconds() const {
        return hardware.getUptime().getMilliseconds();
    }

}
