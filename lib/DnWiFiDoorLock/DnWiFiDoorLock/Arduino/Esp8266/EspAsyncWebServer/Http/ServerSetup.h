#pragma once

#include <type_traits>

#include <ESPAsyncWebServer.h>
#include <WString.h>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Common/Strings.h"
#include "ServoButtonController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/DoorLockController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/FurnaceController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/ServoController.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    class ServerSetup final:
        public DnWiFiDoorLock::Arduino::SetupAndLoopAware {
        using Logger = DnApp::Arduino::Logger::WithArduinoStringLogger;
    public:
        explicit
        ServerSetup(
            ESP8266WiFiClass& wiFi,
            AsyncWebServer& server,
            const char* hostname,
            unsigned int port,
            DoorLockController& doorLockController,
            FurnaceController& furnaceController,
            ServoButtonController& servoButtonController,
            ServoController& servoController,
            Logger& logger
        );

        void onSetup() override;

        void onLoop() override;
    private:
        AsyncWebServer& server;

        ESP8266WiFiClass& wiFi;

        const char* const hostname;

        const unsigned int port;

        // todo: controllers should register themselves to avoid having 2137 controllers here?
        DoorLockController& doorLockController;

        FurnaceController& furnaceController;

        ServoButtonController& servoButtonController;

        ServoController& servoController;

        Logger& logger;

        void handleWebNotFound(AsyncWebServerRequest& request);

        void setupRouting();

        // todo: is there a way to avoid declaring private methods in header file? looks unnecessary to me ;)
        void logServerHasStarted();

        String dataToString(const uint8_t* data, size_t dataLength) const;
    };

    static_assert(!std::is_abstract<ServerSetup>());
}
