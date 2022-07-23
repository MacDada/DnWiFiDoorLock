#include "LoopIndicator.h"

namespace DnWiFiDoorLock::Arduino {

    LoopIndicator::LoopIndicator(Led &led, Logger::ArduinoLogger &logger): led(led), logger(logger) {
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

        String log = "The loop is running… [RSSI: ";
        // todo: get rid of the global var
        log += ::WiFi.RSSI();
        log += "dBm]";

        logger.log(log);
    }

}
