#include "LoopAwareSignalStrengthLogger.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::WiFi {
    LoopAwareSignalStrengthLogger::LoopAwareSignalStrengthLogger(
        ESP8266WiFiClass& esp8266WiFi,
        Logger& logger
    ):
        esp8266WiFi{esp8266WiFi},
        logger{logger} {
    }

    void LoopAwareSignalStrengthLogger::onSetup() {
        // do nothing
    }

    void LoopAwareSignalStrengthLogger::onLoop() {
        log();
    }

    void LoopAwareSignalStrengthLogger::log() {
        String message = F("WiFi ");

        if (esp8266WiFi.isConnected()) {
            message += F("signal strength: ");
            message += esp8266WiFi.RSSI();
            message += F(" dBm");

            logger.debug(message);
        } else {
            // todo: log that it has reconnected after connection problem
            message += F("NOT connected!");

            logger.error(message);
        }
    }
}
