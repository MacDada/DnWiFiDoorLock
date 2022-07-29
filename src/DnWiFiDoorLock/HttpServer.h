#pragma once

#include <type_traits>

#include <ESP8266mDNS.h>

#include "ESPAsyncWebServer.h"

#include "Arduino/Esp8266/EspAsyncWebServer/Http/DoorLockController.h"
#include "Arduino/Esp8266/EspAsyncWebServer/Http/ServoController.h"
#include "Arduino/SetupAndLoopAware.h"
#include "Logger/ArduinoLogger.h"
#include "Tools.h"

namespace DnWiFiDoorLock {

    using Arduino::Esp8266::EspAsyncWebServer::Http::DoorLockController;
    using Arduino::Esp8266::EspAsyncWebServer::Http::ServoController;

    class HttpServer final: public Arduino::SetupAndLoopAware {
    public:
        HttpServer(
            AsyncWebServer &server,
            const char *serverHostName,
            const unsigned int serverPort,
            DoorLockController &doorLockController,
            ServoController &servoController,
            Logger::ArduinoLogger &logger
        );

        void onSetup() override;

        void onLoop() override;

    private:
        AsyncWebServer &server;

        const char *serverHostName;

        unsigned int serverPort;

        // todo: controllers should register themselves to avoid having 2137 controllers here?
        DoorLockController &doorLockController;

        ServoController &servoController;

        Logger::ArduinoLogger &logger;

        void handleWebNotFound(AsyncWebServerRequest *request);

        // todo: is there a way to avoid declaring private methods in header file? looks unnecessary to me ;)
        void logServerHasStarted(const bool mdnsHasStarted);
    };

    static_assert(!std::is_abstract<HttpServer>());

}
