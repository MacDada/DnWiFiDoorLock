#include "Servo.h"

namespace DnWiFiDoorLock::Arduino::Servo {

    Servo::Servo(
        ::Servo &servo,
        byte pin,
        int minPulseWidthMicroseconds,
        int maxPulseWidthMicroseconds,
        DnWiFiDoorLock::Arduino::Logger::Logger &logger
    ):
        servo(servo),
        logger(logger) {
        servo.attach(pin, minPulseWidthMicroseconds, maxPulseWidthMicroseconds);
    }

    int Servo::getAngle() const {
        return servo.read();
    }

    void Servo::setAngle(int degrees) {
        if (degrees < MIN_ANGLE) {
            degrees = MIN_ANGLE;
        } else if (degrees > MAX_ANGLE) {
            degrees = MAX_ANGLE;
        }

        logger.log(Tools::format("Servo: setAngle: write: %d", degrees).get());

        servo.write(degrees);
    }

}
