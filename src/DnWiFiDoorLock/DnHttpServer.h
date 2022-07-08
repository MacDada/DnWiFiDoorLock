#pragma once

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "DnTools.h"
#include "DnHttpController.h"

namespace DnWiFiDoorLock {
    class DnHttpServer {
    public:
        DnHttpServer(
            ESP8266WebServer &server,
            const char *serverHostName,
            const unsigned int serverPort,
            DnHttpController &doorLockController
        );

        void start();

        void handleRequests();

    private:
        ESP8266WebServer *server;
        const char *serverHostName;
        unsigned int serverPort;
        DnHttpController *doorLockController;

        void handleWebNotFound();
    };
}
