#pragma once

#include "ESPAsyncWebServer.h"
#include <ESP8266mDNS.h>
#include "DnTools.h"
#include "DnHttpController.h"

namespace DnWiFiDoorLock {
    class DnHttpServer {
    public:
        DnHttpServer(
            AsyncWebServer &server,
            const char *serverHostName,
            const unsigned int serverPort,
            DnHttpController &doorLockController
        );

        void start();

        void handleRequests();

    private:
        AsyncWebServer *server;
        const char *serverHostName;
        unsigned int serverPort;
        DnHttpController *doorLockController;

        void handleWebNotFound(AsyncWebServerRequest *request);
    };
}
