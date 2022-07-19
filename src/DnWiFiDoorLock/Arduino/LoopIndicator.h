#pragma once

#include <type_traits>

#include <ESP8266WiFi.h>

#include "SetupAndLoopAware.h"
#include "../Led.h"
#include "../Logger/Logger.h"
#include "../Tools.h"

namespace DnWiFiDoorLock::Arduino {

    class LoopIndicator final: public SetupAndLoopAware {
    public:
        LoopIndicator(Led &led, Logger::Logger &logger);

        void onSetup() override;

        void onLoop() override;

    private:
        Led &led;

        Logger::Logger &logger;

        bool hasLoopStarted = false;

        void informTheLoopIsRunning();

        void informThatTheLoopHasStarted();
    };

    static_assert(!std::is_abstract<LoopIndicator>());

}
