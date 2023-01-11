#include "Controller.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    bool Controller::isRequestMethodPost(
        const AsyncWebServerRequest &request
    ) const {
        return 0 == strcmp(request.methodToString(), PSTR("POST"));
    }

    std::optional<String> Controller::getRequestPostParameter(
        AsyncWebServerRequest &request,
        const char *const parameterName
    ) const {
        return request.hasParam(parameterName, true)
           ? request.getParam(parameterName, true)->value()
           : std::optional<String>{};
    }

    void Controller::redirect(
        AsyncWebServerRequest &request,
        const String& location
    ) const {
        // request->redirect("/") is wrong as it sends 302
        AsyncWebServerResponse *const response = request.beginResponse(
            HTTP_RESPONSE_STATUS_REDIRECT
        );
        response->addHeader(F("Location"), location);
        request.send(response);
    }
}
