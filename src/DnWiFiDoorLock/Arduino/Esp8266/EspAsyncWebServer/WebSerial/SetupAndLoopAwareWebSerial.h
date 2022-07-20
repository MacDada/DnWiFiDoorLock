#pragma once

#include <type_traits>

#include <Arduino.h>

#include "ESPAsyncWebServer.h"
#include <WebSerial.h>

#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Tools.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial {

    class SetupAndLoopAwareWebSerial: public SetupAndLoopAware {
    public:
        SetupAndLoopAwareWebSerial(WebSerialClass &serial, AsyncWebServer &server);

        void onSetup() override;

        void onLoop() override;

    private:
        WebSerialClass &serial;

        AsyncWebServer &server;

        void onWebSerialIncoming(uint8_t *message, size_t messageLength);
    };

    static_assert(!std::is_abstract<SetupAndLoopAwareWebSerial>());

}
