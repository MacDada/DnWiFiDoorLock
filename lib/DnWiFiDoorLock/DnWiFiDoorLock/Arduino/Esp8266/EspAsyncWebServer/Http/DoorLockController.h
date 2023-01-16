#pragma once

#include <ESPAsyncWebServer.h>
#include <WString.h>

#include "DnApp/Logger/Logger.h"
#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/DoorLock.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/Controller.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    class DoorLockController final:
        public Controller {
    public:
        DoorLockController(
            const DnWiFiDoorLock::Arduino::Hardware& hardware,
            DnWiFiDoorLock::Arduino::DoorLock& doorLock,
            DnApp::Logger::Logger& logger
        );

        void statusAction(AsyncWebServerRequest& request) const;

        void switchAction(AsyncWebServerRequest& request);
    private:
        const DnWiFiDoorLock::Arduino::Hardware& hardware;

        DnWiFiDoorLock::Arduino::DoorLock& doorLock;

        DnApp::Logger::Logger& logger;
    };

    static_assert(!std::is_abstract<DoorLockController>());
}
