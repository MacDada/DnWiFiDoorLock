#include "LoopIndicator.h"

namespace DnWiFiDoorLock::Arduino {

    LoopIndicator::LoopIndicator(
        const Led &led,
        const LedBlinker &ledBlinker,
        Logger::Logger &logger
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
            logger.log(Logger::Logger::LOG_LEVEL::INFO, "The Loop has started!");
            ledBlinker.blinkFast(5);

            hasLoopStarted = true;
        }
    }

    void LoopIndicator::informTheLoopIsRunning() {
        informThatTheLoopHasStarted();

        led.toggle();
    }

}
