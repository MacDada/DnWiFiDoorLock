#include "LoopAwareSignalStrengthLogger.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::WiFi {

    LoopAwareSignalStrengthLogger::LoopAwareSignalStrengthLogger(
        ESP8266WiFiClass &esp8266WiFi,
        Hardware &hardware,
        Logger::ArduinoLogger &logger
    ):
        esp8266WiFi(esp8266WiFi),
        hardware(hardware),
        logger(logger) {
    }

    void LoopAwareSignalStrengthLogger::onSetup() {
        // do nothing
    }

    void LoopAwareSignalStrengthLogger::onLoop() {
        maybeLog();
    }

    void LoopAwareSignalStrengthLogger::maybeLog() {
        // todo: extract ThrottledLoopAware? ;]
        if (isItTimeToLog()) {
            log();
        }
    }

    bool LoopAwareSignalStrengthLogger::isItTimeToLog() {
        return hardware.getUptime().getMilliseconds() > (lastLogUptimeMilliseconds + INTERVAL_MILLISECONDS);
    }

    void LoopAwareSignalStrengthLogger::log() {
        String message = "WiFi signal strength: ";
        message += esp8266WiFi.RSSI();
        message += " dBm";

        logger.log(message);

        lastLogUptimeMilliseconds = hardware.getUptime().getMilliseconds();
    }
}
