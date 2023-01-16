#include "Servo.h"

namespace DnWiFiDoorLock::Arduino::Servo {
    Servo::Servo(
        ::Servo& servo,
        const byte pin,
        const int minPulseWidthMicroseconds,
        const int maxPulseWidthMicroseconds,
        DnApp::Arduino::Logger::Logger& logger
    ):
        servo{servo},
        logger{logger} {
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

        logger.info(DnApp::Common::Strings::format(
            PSTR("Servo: setAngle: write: %d"),
            degrees
        ));

        servo.write(degrees);
    }
}
