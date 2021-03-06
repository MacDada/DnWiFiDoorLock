#pragma once

#include <type_traits>

#include <ESP8266mDNS.h>

#include "ESPAsyncWebServer.h"

#include "Arduino/SetupAndLoopAware.h"
#include "HttpController.h"
#include "Logger/ArduinoLogger.h"
#include "Tools.h"

namespace DnWiFiDoorLock {

class HttpServer final: public Arduino::SetupAndLoopAware {
    public:
        HttpServer(
            AsyncWebServer &server,
            const char *serverHostName,
            const unsigned int serverPort,
            HttpController &doorLockController,
            Logger::ArduinoLogger &logger
        );

        void onSetup() override;

        void onLoop() override;

    private:
        AsyncWebServer &server;
        const char *serverHostName;
        unsigned int serverPort;
        HttpController &doorLockController;
        Logger::ArduinoLogger &logger;

        void handleWebNotFound(AsyncWebServerRequest *request);

        // todo: is there a way to avoid declaring private methods in header file? looks unnecessary to me ;)
        void logServerHasStarted(const bool mdnsHasStarted);
    };

    static_assert(!std::is_abstract<HttpServer>());

}
