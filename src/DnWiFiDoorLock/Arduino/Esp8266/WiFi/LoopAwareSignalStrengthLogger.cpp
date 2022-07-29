#include "LoopAwareSignalStrengthLogger.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::WiFi {

    LoopAwareSignalStrengthLogger::LoopAwareSignalStrengthLogger(
        ESP8266WiFiClass &esp8266WiFi,
        Logger::ArduinoLogger &logger
    ):
        esp8266WiFi(esp8266WiFi),
        logger(logger) {
    }

    void LoopAwareSignalStrengthLogger::onSetup() {
        // do nothing
    }

    void LoopAwareSignalStrengthLogger::onLoop() {
        log();
    }

    void LoopAwareSignalStrengthLogger::log() {
        String message = "WiFi signal strength: ";
        message += esp8266WiFi.RSSI();
        message += " dBm";

        logger.log(message);
    }

}
