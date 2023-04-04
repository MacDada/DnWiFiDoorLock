#pragma once

#include <cstdint> // uint8_t

#include <Servo.h>
#include <WString.h>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Common/Strings.h"
#include "DnApp/Hardware/Servo.h"

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
    class Servo final:
        public DnApp::Hardware::Servo {
    public:
        Servo(
            ::Servo& servo,
            const uint8_t pin,
            const int minPulseWidthMicroseconds,
            const int maxPulseWidthMicroseconds,
            DnApp::Arduino::Logger::WithArduinoStringLogger& logger
        ):
            servo{servo},
            logger{logger} {
            servo.attach(pin, minPulseWidthMicroseconds, maxPulseWidthMicroseconds);
        }

        auto getAngle() const -> Angle override {
            // todo: test if the "default" (or random?) value does not actually throw
            return Angle::withDegrees(servo.read()).value();
        }

        auto setAngle(const Angle angle) -> void override {
            logger.info(DnApp::Common::Strings::format(
                PSTR("Servo: setAngle: write: %d"),
                angle.getDegrees()
            ));

            servo.write(angle.getDegrees());
        }
    private:
        ::Servo& servo;

        DnApp::Arduino::Logger::WithArduinoStringLogger& logger;
    };
}
