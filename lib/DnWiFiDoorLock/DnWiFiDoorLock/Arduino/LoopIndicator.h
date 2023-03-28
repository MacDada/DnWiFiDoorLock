#pragma once

#include <type_traits> // std::is_abstract

#include <ESP8266WiFi.h>
#include <WString.h>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Hardware/Led.h"
#include "DnWiFiDoorLock/Arduino/LedBlinker.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class LoopIndicator final:
        public SetupAndLoopAware {
    public:
        explicit
        LoopIndicator(
            DnApp::Hardware::Led& led,
            LedBlinker& ledBlinker,
            DnApp::Arduino::Logger::WithArduinoStringLogger& logger
        ):
            led{led},
            ledBlinker{ledBlinker},
            logger{logger} {
        }

        auto onSetup() -> void override {
            // do nothing
        }

        auto onLoop() -> void override {
            informTheLoopIsRunning();
        }
    private:
        DnApp::Hardware::Led& led;

        LedBlinker& ledBlinker;

        DnApp::Arduino::Logger::WithArduinoStringLogger& logger;

        bool hasLoopStarted = false;

        auto informThatTheLoopHasStarted() -> void {
            if (!hasLoopStarted) {
                logger.info(PSTR("The Loop has started!"));
                ledBlinker.blinkFast(5);

                hasLoopStarted = true;
            }
        }

        auto informTheLoopIsRunning() -> void {
            informThatTheLoopHasStarted();

            // todo: maybe it would be possible to dim the led a bit?
            //       so that there would be a bright and dark version?
            led.toggle();
        }
    };

    static_assert(!std::is_abstract<LoopIndicator>());
}
