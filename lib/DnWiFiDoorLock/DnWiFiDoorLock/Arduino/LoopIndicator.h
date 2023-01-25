#pragma once

#include <type_traits>

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

        void onSetup() override {
            // do nothing
        }

        void onLoop() override {
            informTheLoopIsRunning();
        }
    private:
        DnApp::Hardware::Led& led;

        LedBlinker& ledBlinker;

        DnApp::Arduino::Logger::WithArduinoStringLogger& logger;

        bool hasLoopStarted = false;

        void informThatTheLoopHasStarted() {
            if (!hasLoopStarted) {
                logger.info(F("The Loop has started!"));
                ledBlinker.blinkFast(5);

                hasLoopStarted = true;
            }
        }

        void informTheLoopIsRunning() {
            informThatTheLoopHasStarted();

            // todo: maybe it would be possible to dim the led a bit?
            //       so that there would be a bright and dark version?
            led.toggle();
        }
    };

    static_assert(!std::is_abstract<LoopIndicator>());
}
