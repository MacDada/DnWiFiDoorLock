#pragma once

#include <ESPAsyncWebServer.h>

#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/Controller.h"
#include "DnWiFiDoorLock/Furnace.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Logger/Logger.h"
#include "DnWiFiDoorLock/Tools.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    class FurnaceController final: public Controller {
    public:
        explicit FurnaceController(
            const DnWiFiDoorLock::Arduino::Hardware &hardware,
            DnWiFiDoorLock::Furnace &furnace,
            DnWiFiDoorLock::Logger::Logger &logger
        );

        void statusAction(AsyncWebServerRequest &request) const;

        void switchAction(AsyncWebServerRequest &request) const;

        void apiAction(AsyncWebServerRequest &request) const;

    private:
        const DnWiFiDoorLock::Arduino::Hardware &hardware;

        DnWiFiDoorLock::Furnace &furnace;

        DnWiFiDoorLock::Logger::Logger &logger;
    };

    static_assert(!std::is_abstract<FurnaceController>());

}
