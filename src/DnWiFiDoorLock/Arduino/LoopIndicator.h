#pragma once

#include <type_traits>

#include <ESP8266WiFi.h>

#include "DnWiFiDoorLock/Arduino/Led.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Logger/ArduinoLogger.h"

namespace DnWiFiDoorLock::Arduino {

    class LoopIndicator final: public SetupAndLoopAware {
    public:
        LoopIndicator(Led &led, Logger::ArduinoLogger &logger);

        void onSetup() override;

        void onLoop() override;

    private:
        Led &led;

        Logger::ArduinoLogger &logger;

        bool hasLoopStarted = false;

        void informTheLoopIsRunning();

        void informThatTheLoopHasStarted();
    };

    static_assert(!std::is_abstract<LoopIndicator>());

}
