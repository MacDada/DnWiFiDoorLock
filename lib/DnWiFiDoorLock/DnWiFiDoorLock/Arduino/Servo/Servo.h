#pragma once

#include <Servo.h>
#include <WString.h>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"

// todo: servo power supply:
//       * should I detach()?
//          * probably yes
//              * uC constantly sends signal to position the servo, no matter if i do write() once or repeatedly in a loop
//              * internet ppl say detach() stops sending the signal -> question is, what servo does then?
//          * "There might be a very small current drawn by a detach()-ed servo, but I doubt if it’s significant."
// todo: how much torque do I need?
//       * 1Nm? https://www.quora.com/How-much-torque-does-it-require-to-turn-a-key-in-a-door-lock-in-general
//       * 0,3 Nm = 3,1kg*cm => i need ~12kg*cm
// todo: low battery level detection
//       * https://community.home-assistant.io/t/esp8266-on-4-aa-batteries-needing-a-low-battery-level-notificaiton/426672/17
//
// cables:
//      * brown: GND
//      * red: power
//      * orange: control
namespace DnWiFiDoorLock::Arduino::Servo {
    class Servo final {
    public:
        static const int MIN_ANGLE = 0;

        static const int MAX_ANGLE = 180;

        Servo(
            ::Servo& servo,
            const byte pin,
            const int minPulseWidthMicroseconds,
            const int maxPulseWidthMicroseconds,
            DnApp::Arduino::Logger::WithArduinoStringLogger& logger
        ):
            servo{servo},
            logger{logger} {
            servo.attach(pin, minPulseWidthMicroseconds, maxPulseWidthMicroseconds);
        }

        auto getAngle() const -> int {
            return servo.read();
        }

        auto setAngle(int degrees) -> void {
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
    private:
        ::Servo& servo;

        DnApp::Arduino::Logger::WithArduinoStringLogger& logger;
    };
}
