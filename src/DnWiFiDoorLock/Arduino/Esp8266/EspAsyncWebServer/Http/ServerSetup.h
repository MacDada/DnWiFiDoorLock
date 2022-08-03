#pragma once

#include <type_traits>

#include <ESPAsyncWebServer.h>

#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/DoorLockController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/ServoController.h"
#include "DnWiFiDoorLock/Arduino/Logger/Logger.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Tools.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    class ServerSetup final: public DnWiFiDoorLock::Arduino::SetupAndLoopAware {
        using Logger = DnWiFiDoorLock::Arduino::Logger::Logger;

    public:
        ServerSetup(
            AsyncWebServer &server,
            const char *hostname,
            unsigned int port,
            DoorLockController &doorLockController,
            ServoController &servoController,
            Logger &logger
        );

        void onSetup() override;

        void onLoop() override;

    private:
        AsyncWebServer &server;

        const char *const hostname;

        const unsigned int port;

        // todo: controllers should register themselves to avoid having 2137 controllers here?
        DoorLockController &doorLockController;

        ServoController &servoController;

        Logger &logger;

        void handleWebNotFound(AsyncWebServerRequest &request);

        void setupRouting();

        // todo: is there a way to avoid declaring private methods in header file? looks unnecessary to me ;)
        void logServerHasStarted();
    };

    static_assert(!std::is_abstract<ServerSetup>());

}
