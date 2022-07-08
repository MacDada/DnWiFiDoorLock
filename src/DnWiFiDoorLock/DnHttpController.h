#pragma once

#include <ESP8266WebServer.h>

#include "DnHardware.h"
#include "DnDoorLock.h"
#include "DnTools.h"

namespace DnWiFiDoorLock {
    class DnHttpController {
    public:
        DnHttpController(DnHardware &hardware, DnDoorLock &doorLock);

        void statusAction(ESP8266WebServer &server);

        void switchAction(ESP8266WebServer &server);

    private:
        static const int HTTP_RESPONSE_STATUS_OK = 200;
        static const int HTTP_RESPONSE_STATUS_METHOD_NOT_ALLOWED = 405;
        static const int HTTP_RESPONSE_STATUS_REDIRECT = 303;
        static constexpr char HTTP_RESPONSE_CONTENT_TYPE_PLAIN[] = "text/plain";
        static constexpr char HTTP_RESPONSE_CONTENT_TYPE_HTML[] = "text/html";

        DnHardware *hardware;
        DnDoorLock *doorLock;
    };
}
