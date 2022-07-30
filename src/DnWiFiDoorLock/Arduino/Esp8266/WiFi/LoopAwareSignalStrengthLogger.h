#pragma once

#include <type_traits>

#include <ESP8266WiFi.h>

#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/Logger/ArduinoLogger.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::WiFi {

    class LoopAwareSignalStrengthLogger final: public Arduino::SetupAndLoopAware {
        using Logger = DnWiFiDoorLock::Arduino::Logger::ArduinoLogger;

    public:
        LoopAwareSignalStrengthLogger(
            ESP8266WiFiClass &esp8266WiFi,
            Logger &logger
        );

        void onSetup() override;

        void onLoop() override;

    private:
        ESP8266WiFiClass &esp8266WiFi;

        Logger &logger;

        void log();
    };

    static_assert(!std::is_abstract<LoopAwareSignalStrengthLogger>());

}
