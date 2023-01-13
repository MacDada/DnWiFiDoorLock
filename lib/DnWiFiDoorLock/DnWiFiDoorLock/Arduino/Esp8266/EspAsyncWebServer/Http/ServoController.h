#pragma once

#include <optional>
#include <type_traits>

#include <ESPAsyncWebServer.h>
#include <WString.h>

#include "DnApp/Logger/Logger.h"
#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/Controller.h"
#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    class ServoController final: public Controller {
        using Logger = DnApp::Logger::Logger;
        using Request = AsyncWebServerRequest;
        using Servo = DnWiFiDoorLock::Arduino::Servo::Servo;
    public:
        explicit
        ServoController(
            Servo& servo,
            Logger& logger,
            const char* const appName
        );

        void angleAction(AsyncWebServerRequest& request);
    private:
        Servo& servo;

        Logger& logger;

        const char* const appName;

        String renderAngleResponse(
            int oldAngle,
            std::optional<int> newAngle = {},
            bool invalidAngle = false
        ) const;

        bool isValidAngle(int angle) const;

        void showCurrentAngleResponse(Request& request, int oldAngle);

        void invalidAngleGivenResponse(Request& request, int oldAngle, int newAngle);

        void newAngleSetResponse(Request& request, int oldAngle, int newAngle);
    };

    static_assert(!std::is_abstract<ServoController>());
}
