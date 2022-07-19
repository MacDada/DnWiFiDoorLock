#include "LoopIndicator.h"

namespace DnWiFiDoorLock::Arduino {

    LoopIndicator::LoopIndicator(Led &led, Logger::Logger &logger): led(led), logger(logger) {
    }

    void LoopIndicator::onSetup() {
        // do nothing
    }

    void LoopIndicator::onLoop() {
        informTheLoopIsRunning();
    }

    void LoopIndicator::informThatTheLoopHasStarted() {
        if (!hasLoopStarted) {
            logger.log("The Loop has started!");
            led.blinkFast(5);

            hasLoopStarted = true;
        }
    }

    void LoopIndicator::informTheLoopIsRunning() {
        informThatTheLoopHasStarted();

        led.blink1sPause1s();
        // todo: get rid of the global var
        logger.log(Tools::format("The loop is running… [RSSI: %d dBm]", ::WiFi.RSSI()));
    }

}
