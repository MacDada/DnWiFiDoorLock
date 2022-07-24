#pragma once

#include <type_traits>

#include <ESP8266WiFi.h>

#include "../../../Hardware.h"
#include "../../../Logger/ArduinoLogger.h"
#include "../../SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::WiFi {

    class LoopAwareSignalStrengthLogger final: public Arduino::SetupAndLoopAware {
    public:
        LoopAwareSignalStrengthLogger(
            ESP8266WiFiClass &esp8266WiFi,
            Hardware &hardware,
            Logger::ArduinoLogger &logger
        );

        void onSetup() override;

        void onLoop() override;

    private:
        static const unsigned int INTERVAL_MILLISECONDS = 1000;

        unsigned long lastLogUptimeMilliseconds = 0;

        ESP8266WiFiClass &esp8266WiFi;

        Hardware &hardware;

        Logger::ArduinoLogger &logger;

        void maybeLog();

        bool isItTimeToLog();

        void log();
    };

    static_assert(!std::is_abstract<LoopAwareSignalStrengthLogger>());

}
