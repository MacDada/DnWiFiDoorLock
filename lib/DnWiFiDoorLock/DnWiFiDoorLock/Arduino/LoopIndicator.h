#pragma once

#include <type_traits>

#include <ESP8266WiFi.h>
#include <WString.h>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Hardware/Led.h"
#include "DnWiFiDoorLock/Arduino/LedBlinker.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class LoopIndicator final:
        public SetupAndLoopAware {
    public:
        LoopIndicator(
            DnApp::Hardware::Led& led,
            LedBlinker& ledBlinker,
            DnApp::Arduino::Logger::WithArduinoStringLogger& logger
        );

        void onSetup() override;

        void onLoop() override;
    private:
        DnApp::Hardware::Led& led;

        LedBlinker& ledBlinker;

        DnApp::Arduino::Logger::WithArduinoStringLogger& logger;

        bool hasLoopStarted = false;

        void informTheLoopIsRunning();

        void informThatTheLoopHasStarted();
    };

    static_assert(!std::is_abstract<LoopIndicator>());
}
