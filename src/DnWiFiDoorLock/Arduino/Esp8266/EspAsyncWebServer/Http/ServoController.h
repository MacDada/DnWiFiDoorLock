#pragma once

#include <optional>
#include <type_traits>

#include <ESPAsyncWebServer.h>

#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"
#include "DnWiFiDoorLock/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    using DnWiFiDoorLock::Arduino::Servo::Servo;
    using Request = AsyncWebServerRequest;

    class ServoController final {
    public:
        explicit ServoController(
            Servo &servo,
            Logger::Logger &logger
        );

        void angleAction(AsyncWebServerRequest &request);

    private:
        // todo: extract enum/class
        static const int HTTP_RESPONSE_STATUS_OK = 200;
        static const int HTTP_RESPONSE_STATUS_ACCEPTED = 202;
        static const int HTTP_RESPONSE_STATUS_REDIRECT = 303;
        static const int HTTP_RESPONSE_STATUS_BAD_REQUEST = 400;
        static const int HTTP_RESPONSE_STATUS_METHOD_NOT_ALLOWED = 405;

        static constexpr char HTTP_RESPONSE_CONTENT_TYPE_PLAIN[] = "text/plain";
        static constexpr char HTTP_RESPONSE_CONTENT_TYPE_HTML[] = "text/html";

        Servo &servo;

        Logger::Logger &logger;

        String renderAngleResponse(
            int oldAngle,
            std::optional<int> newAngle = {},
            bool invalidAngle = false
        ) const;

        bool isValidAngle(int angle) const;

        void showCurrentAngleResponse(Request &request, int oldAngle);

        void invalidAngleGivenResponse(Request &request, int oldAngle, int newAngle);

        void newAngleSetResponse(Request &request, int oldAngle, int newAngle);

        // todo: extract BaseController
        std::optional<String> getRequestPostParameter(
            Request &request,
            const char *parameterName
        ) const;
    };

    static_assert(!std::is_abstract<ServoController>());

}
