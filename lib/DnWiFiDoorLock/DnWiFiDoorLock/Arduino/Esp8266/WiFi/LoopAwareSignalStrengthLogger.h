#pragma once

#include <type_traits>

#include <ESP8266WiFi.h>
#include <WString.h>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::WiFi {
    class LoopAwareSignalStrengthLogger final:
        public Arduino::SetupAndLoopAware {
    private:
        using Logger = DnApp::Arduino::Logger::WithArduinoStringLogger;
    public:
        explicit
        LoopAwareSignalStrengthLogger(
            ESP8266WiFiClass& esp8266WiFi,
            Logger& logger
        ):
            esp8266WiFi{esp8266WiFi},
            logger{logger} {
        }

        void onSetup() override {
            // do nothing
        }

        void onLoop() override {
            log();
        }
    private:
        ESP8266WiFiClass& esp8266WiFi;

        Logger& logger;

        void log() {
            String message = PSTR("WiFi ");

            if (esp8266WiFi.isConnected()) {
                message += PSTR("signal strength: ");
                message += esp8266WiFi.RSSI();
                message += PSTR(" dBm");

                logger.debug(message);
            } else {
                message += PSTR("is NOT connected!");

                logger.error(message);
            }
        }
    };

    static_assert(!std::is_abstract<LoopAwareSignalStrengthLogger>());
}
