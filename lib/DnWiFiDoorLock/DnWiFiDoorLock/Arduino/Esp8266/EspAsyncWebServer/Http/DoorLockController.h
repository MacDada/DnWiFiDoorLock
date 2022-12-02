#pragma once

#include <ESPAsyncWebServer.h>

#include "DnWiFiDoorLock/Arduino/DoorLock.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/Controller.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Logger/Logger.h"
#include "DnWiFiDoorLock/Tools.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    class DoorLockController final: public Controller {
    public:
        DoorLockController(
            const DnWiFiDoorLock::Arduino::Hardware &hardware,
            DnWiFiDoorLock::Arduino::DoorLock &doorLock,
            DnWiFiDoorLock::Logger::Logger &logger
        );

        void statusAction(AsyncWebServerRequest &request) const;

        void switchAction(AsyncWebServerRequest &request);

    private:
        const DnWiFiDoorLock::Arduino::Hardware &hardware;

        DnWiFiDoorLock::Arduino::DoorLock &doorLock;

        DnWiFiDoorLock::Logger::Logger &logger;
    };

    static_assert(!std::is_abstract<DoorLockController>());

}
