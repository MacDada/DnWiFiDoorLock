#include "LoopIndicator.h"

namespace DnWiFiDoorLock::Arduino {
    LoopIndicator::LoopIndicator(
        const Led &led,
        const LedBlinker &ledBlinker,
        DnApp::Arduino::Logger::Logger &logger
    ) :
        led(led),
        ledBlinker(ledBlinker),
        logger(logger) {
    }

    void LoopIndicator::onSetup() {
        // do nothing
    }

    void LoopIndicator::onLoop() {
        informTheLoopIsRunning();
    }

    void LoopIndicator::informThatTheLoopHasStarted() {
        if (!hasLoopStarted) {
            logger.info("The Loop has started!");
            ledBlinker.blinkFast(5);

            hasLoopStarted = true;
        }
    }

    void LoopIndicator::informTheLoopIsRunning() {
        informThatTheLoopHasStarted();

        led.toggle();
    }
}
