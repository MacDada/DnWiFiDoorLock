#pragma once

#include <optional>

#include <ESPAsyncWebServer.h>
#include <WString.h>

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    class Controller {
    protected:
        static
        const
        auto HTTP_RESPONSE_STATUS_OK = 200;

        static
        const
        auto HTTP_RESPONSE_STATUS_ACCEPTED = 202;

        static
        const
        auto HTTP_RESPONSE_STATUS_REDIRECT = 303;

        static
        const
        auto HTTP_RESPONSE_STATUS_BAD_REQUEST = 400;

        static
        const
        auto HTTP_RESPONSE_STATUS_METHOD_NOT_ALLOWED = 405;

        static
        const
        auto HTTP_RESPONSE_STATUS_INTERNAL_SERVER_ERROR = 500;

        static
        PROGMEM
        constexpr
        const
        auto HTTP_RESPONSE_CONTENT_TYPE_PLAIN = "text/plain";

        static
        PROGMEM
        constexpr
        const
        auto HTTP_RESPONSE_CONTENT_TYPE_HTML = "text/html";

        static
        PROGMEM
        constexpr
        const
        auto HTTP_RESPONSE_CONTENT_TYPE_JSON = "application/json";

        static
        PROGMEM
        constexpr
        const
        auto HTTP_RESPONSE_CONTENT_TYPE_CSS = "text/css";

        // https://stackoverflow.com/a/21098951/666907
        static
        PROGMEM
        constexpr
        const
        auto HTTP_RESPONSE_CONTENT_TYPE_JAVASCRIPT = "text/javascript";

        [[nodiscard]]
        auto isRequestMethodPost(
            const AsyncWebServerRequest& request
        ) const -> bool {
            return 0 == strcmp(request.methodToString(), PSTR("POST"));
        }

        std::optional<String> getRequestPostParameter(
            const AsyncWebServerRequest& request,
            const char* const parameterName
        ) const {
            return request.hasParam(parameterName, true)
                ? request.getParam(parameterName, true)->value()
                : std::optional<String>{};
        }

        auto redirect(
            AsyncWebServerRequest& request,
            const String& location
        ) const -> void {
            // request->redirect("/") is wrong as it sends 302
            AsyncWebServerResponse* const response = request.beginResponse(
                HTTP_RESPONSE_STATUS_REDIRECT
            );
            response->addHeader(PSTR("Location"), location);
            request.send(response);
        }
    };
}
