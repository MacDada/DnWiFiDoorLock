#pragma once

#include "ESPAsyncWebServer.h"
#include "Hardware.h"
#include "DoorLock.h"
#include "Tools.h"

namespace DnWiFiDoorLock {

    class HttpController final {
    public:
        HttpController(Hardware &hardware, DoorLock &doorLock);

        void statusAction(AsyncWebServerRequest *request);

        void switchAction(AsyncWebServerRequest *request);

    private:
        static const int HTTP_RESPONSE_STATUS_OK = 200;
        static const int HTTP_RESPONSE_STATUS_METHOD_NOT_ALLOWED = 405;
        static const int HTTP_RESPONSE_STATUS_REDIRECT = 303;
        static constexpr char HTTP_RESPONSE_CONTENT_TYPE_PLAIN[] = "text/plain";
        static constexpr char HTTP_RESPONSE_CONTENT_TYPE_HTML[] = "text/html";

        Hardware &hardware;
        DoorLock &doorLock;
    };

}
