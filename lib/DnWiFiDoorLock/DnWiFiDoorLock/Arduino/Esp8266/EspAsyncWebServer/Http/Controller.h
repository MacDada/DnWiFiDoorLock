#pragma once

#include <optional>

#include <ESPAsyncWebServer.h>
#include <WString.h>

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    class Controller {
    protected:
        static const int HTTP_RESPONSE_STATUS_OK = 200;

        static const int HTTP_RESPONSE_STATUS_ACCEPTED = 202;

        static const int HTTP_RESPONSE_STATUS_REDIRECT = 303;

        static const int HTTP_RESPONSE_STATUS_BAD_REQUEST = 400;

        static const int HTTP_RESPONSE_STATUS_METHOD_NOT_ALLOWED = 405;

        static PROGMEM constexpr const char HTTP_RESPONSE_CONTENT_TYPE_PLAIN[] = "text/plain";

        static PROGMEM constexpr const char HTTP_RESPONSE_CONTENT_TYPE_HTML[] = "text/html";

        static PROGMEM constexpr const char HTTP_RESPONSE_CONTENT_TYPE_JSON[] = "application/json";

        static PROGMEM constexpr const char HTTP_RESPONSE_CONTENT_TYPE_CSS[] = "text/css";

        // https://stackoverflow.com/a/21098951/666907
        static PROGMEM constexpr const char HTTP_RESPONSE_CONTENT_TYPE_JAVASCRIPT[] = "text/javascript";

        bool isRequestMethodPost(
            const AsyncWebServerRequest& request
        ) const {
            return 0 == strcmp(request.methodToString(), PSTR("POST"));
        }

        std::optional<String> getRequestPostParameter(
            AsyncWebServerRequest& request,
            const char* const parameterName
        ) const {
            return request.hasParam(parameterName, true)
                ? request.getParam(parameterName, true)->value()
                : std::optional<String>{};
        }

        void redirect(
            AsyncWebServerRequest& request,
            const String& location
        ) const {
            // request->redirect("/") is wrong as it sends 302
            AsyncWebServerResponse* const response = request.beginResponse(
                HTTP_RESPONSE_STATUS_REDIRECT
            );
            response->addHeader(PSTR("Location"), location);
            request.send(response);
        }
    };
}
