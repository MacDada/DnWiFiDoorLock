#include "LoopIndicator.h"

namespace DnWiFiDoorLock::Arduino {
    LoopIndicator::LoopIndicator(
        DnApp::Hardware::Led& led,
        LedBlinker& ledBlinker,
        DnApp::Arduino::Logger::WithArduinoStringLogger& logger
    ):
        led{led},
        ledBlinker{ledBlinker},
        logger{logger} {
    }

    void LoopIndicator::onSetup() {
        // do nothing
    }

    void LoopIndicator::onLoop() {
        informTheLoopIsRunning();
    }

    void LoopIndicator::informThatTheLoopHasStarted() {
        if (!hasLoopStarted) {
            logger.info(F("The Loop has started!"));
            ledBlinker.blinkFast(5);

            hasLoopStarted = true;
        }
    }

    void LoopIndicator::informTheLoopIsRunning() {
        informThatTheLoopHasStarted();

        led.toggle();
    }
}
