#pragma once

#include <ESPAsyncWebServer.h>

#include "DnWiFiDoorLock/Arduino/DoorLock.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Logger/Logger.h"
#include "DnWiFiDoorLock/Tools.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    class DoorLockController final {
    public:
        DoorLockController(
            DnWiFiDoorLock::Arduino::Hardware &hardware,
            DnWiFiDoorLock::Arduino::DoorLock &doorLock,
            DnWiFiDoorLock::Logger::Logger &logger
        );

        void statusAction(AsyncWebServerRequest &request);

        void switchAction(AsyncWebServerRequest &request);

    private:
        // todo: extract enum/class
        static const int HTTP_RESPONSE_STATUS_OK = 200;
        static const int HTTP_RESPONSE_STATUS_REDIRECT = 303;
        static const int HTTP_RESPONSE_STATUS_BAD_REQUEST = 400;
        static const int HTTP_RESPONSE_STATUS_METHOD_NOT_ALLOWED = 405;
        static constexpr char HTTP_RESPONSE_CONTENT_TYPE_PLAIN[] = "text/plain";
        static constexpr char HTTP_RESPONSE_CONTENT_TYPE_HTML[] = "text/html";

        DnWiFiDoorLock::Arduino::Hardware &hardware;

        DnWiFiDoorLock::Arduino::DoorLock &doorLock;

        DnWiFiDoorLock::Logger::Logger &logger;
    };

    static_assert(!std::is_abstract<DoorLockController>());

}
