#pragma once

#include <type_traits>

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>
#include <WString.h>

#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial {
    class Setup:
        public SetupAndLoopAware {
    public:
        explicit
        Setup(WebSerialClass& serial, AsyncWebServer& server);

        void onSetup() override;

        void onLoop() override;

    private:
        WebSerialClass& serial;

        AsyncWebServer& server;

        void onWebSerialIncoming(uint8_t* const message, size_t messageLength);
    };

    static_assert(!std::is_abstract<Setup>());
}
