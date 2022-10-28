#pragma once

#include <optional>

#include <ESPAsyncWebServer.h>

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    class Controller {
    protected:
        static const int HTTP_RESPONSE_STATUS_OK = 200;
        static const int HTTP_RESPONSE_STATUS_ACCEPTED = 202;
        static const int HTTP_RESPONSE_STATUS_REDIRECT = 303;
        static const int HTTP_RESPONSE_STATUS_BAD_REQUEST = 400;
        static const int HTTP_RESPONSE_STATUS_METHOD_NOT_ALLOWED = 405;

        static constexpr const char HTTP_RESPONSE_CONTENT_TYPE_PLAIN[] = "text/plain";
        static constexpr const char HTTP_RESPONSE_CONTENT_TYPE_HTML[] = "text/html";
        static constexpr const char HTTP_RESPONSE_CONTENT_TYPE_JSON[] = "application/json";

        bool isRequestMethodPost(const AsyncWebServerRequest &request) const;

        std::optional<String> getRequestPostParameter(
            AsyncWebServerRequest &request,
            const char *const parameterName
        ) const;

        void redirect(AsyncWebServerRequest &request, const String& location) const;
    };

}
