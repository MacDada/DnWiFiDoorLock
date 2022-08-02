#include "Controller.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    std::optional<String> Controller::getRequestPostParameter(
        AsyncWebServerRequest &request,
        const char *parameterName
    ) const {
        return request.hasParam(parameterName, true)
               ? request.getParam(parameterName, true)->value()
               : std::optional<String>{};
    }

}
