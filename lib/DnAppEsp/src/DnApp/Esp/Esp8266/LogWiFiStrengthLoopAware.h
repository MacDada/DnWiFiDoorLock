#pragma once

#include <type_traits> // std::is_abstract

#include <ESP8266WiFi.h>
#include <WString.h>

#include "DnApp/Arduino/Kernel/SetupAndLoopAware.h"
#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"

namespace DnApp::Esp::Esp8266 {
    class LogWiFiStrengthLoopAware final:
        public DnApp::Arduino::Kernel::SetupAndLoopAware {
    private:
        using Logger = Arduino::Logger::WithArduinoStringLogger;
    public:
        explicit
        LogWiFiStrengthLoopAware(
            ESP8266WiFiClass& esp8266WiFi,
            Logger& logger
        ):
            esp8266WiFi{esp8266WiFi},
            logger{logger} {
        }

        auto onSetup() -> void override {
            // do nothing
        }

        auto onLoop() -> void override {
            log();
        }
    private:
        ESP8266WiFiClass& esp8266WiFi;

        Logger& logger;

        auto log() -> void {
            auto message = String{PSTR("WiFi ")};

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

    static_assert(!std::is_abstract<LogWiFiStrengthLoopAware>());
}
