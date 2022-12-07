#pragma once

#include <ESPAsyncWebServer.h>

#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/Controller.h"
#include "DnWiFiDoorLock/Furnace.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnApp/Logger/Logger.h"
#include "DnWiFiDoorLock/Tools.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    class FurnaceController final: public Controller {
    public:
        explicit FurnaceController(
            const DnWiFiDoorLock::Arduino::Hardware &hardware,
            DnWiFiDoorLock::Furnace &furnace,
            DnApp::Logger::Logger &logger
        );

        void statusAction(AsyncWebServerRequest &request) const;

        void switchAction(AsyncWebServerRequest &request) const;

        void apiGetAction(AsyncWebServerRequest &request) const;

        void apiPostAction(AsyncWebServerRequest &request, const String &body) const;

    private:
        const DnWiFiDoorLock::Arduino::Hardware &hardware;

        DnWiFiDoorLock::Furnace &furnace;

        DnApp::Logger::Logger &logger;
    };

    static_assert(!std::is_abstract<FurnaceController>());

}