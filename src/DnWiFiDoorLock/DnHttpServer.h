#pragma once

#include "ESPAsyncWebServer.h"
#include <ESP8266mDNS.h>
#include "DnTools.h"
#include "DnHttpController.h"
#include "Logger/ArduinoLogger.h"

namespace DnWiFiDoorLock {
    class DnHttpServer {
    public:
        DnHttpServer(
            AsyncWebServer &server,
            const char *serverHostName,
            const unsigned int serverPort,
            DnHttpController &doorLockController,
            Logger::ArduinoLogger &logger
        );

        void start();

        void handleRequests();

    private:
        AsyncWebServer *server;
        const char *serverHostName;
        unsigned int serverPort;
        DnHttpController *doorLockController;
        Logger::ArduinoLogger *logger;

        void handleWebNotFound(AsyncWebServerRequest *request);

        // todo: is there a way to avoid declaring private methods in header file? looks unnecessary to me ;)
        void logServerHasStarted(const bool mdnsHasStarted);
    };
}
