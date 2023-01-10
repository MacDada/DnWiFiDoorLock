#include "ServerSetup.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    ServerSetup::ServerSetup(
        AsyncWebServer &server,
        const char *const hostname,
        const unsigned int port,
        DoorLockController &doorLockController,
        FurnaceController &furnaceController,
        ServoButtonController &servoButtonController,
        ServoController &servoController,
        Logger &logger
    ):
        server(server),
        hostname(hostname),
        port(port),
        doorLockController(doorLockController),
        furnaceController(furnaceController),
        servoButtonController(servoButtonController),
        servoController(servoController),
        logger(logger) {
    }

    void ServerSetup::onSetup() {
        setupRouting();

        server.begin();

        logServerHasStarted();
    }

    void ServerSetup::setupRouting() {
        server.on("/", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            request->redirect("/furnace");
        });

        // https://discord.com/channels/583251190591258624/742849025191051326/995832013405835316
        //
        // todo: can i get null here instead of the object? o.O
        server.on("/doorlock", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            doorLockController.statusAction(*request);
        });

        server.on("/doorlock/switch", HTTP_POST, [&](AsyncWebServerRequest *const request) {
            doorLockController.switchAction(*request);
        });

        server.on("/furnace", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            furnaceController.statusAction(*request);
        });

        server.on("/furnace/switch", HTTP_POST, [&](AsyncWebServerRequest *const request) {
            furnaceController.switchAction(*request);
        });

        server.on("/api/furnace", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            furnaceController.apiGetAction(*request);
        });

        server.on("/api/furnace", HTTP_POST, [&](AsyncWebServerRequest *const request) {
            // ignore, we use the callback with request body
        }, nullptr, [&](
            AsyncWebServerRequest *request,
            uint8_t *bodyData,
            size_t bodyDataLength,
            size_t index,
            size_t total
        ) {
            String body = dataToString(bodyData, bodyDataLength);

            furnaceController.apiPostAction(*request, body);
        });

        server.on("/modal.css", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            servoButtonController.modalCssAction(*request);
        });

        server.on("/modal.js", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            servoButtonController.modalJsAction(*request);
        });

        server.on("/ajax-form.js", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            servoButtonController.ajaxFormJsAction(*request);
        });

        server.on("/input-number-buttons.js", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            servoButtonController.inputNumberButtonsJsAction(*request);
        });

        server.on("/servo-button.js", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            servoButtonController.javascriptAction(*request);
        });

        server.on("/servo-button.css", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            servoButtonController.cssAction(*request);
        });

        server.on("/servo-button", HTTP_POST, [&](AsyncWebServerRequest *const request) {
            servoButtonController.updateSettingsAction(*request);
        });

        server.on("/servo-button", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            servoButtonController.showSettingsAction(*request);
        });

        server.on("/servo", HTTP_GET | HTTP_POST, [&](AsyncWebServerRequest *const request) {
            servoController.angleAction(*request);
        });

        server.onNotFound([&](AsyncWebServerRequest *const request) {
            handleWebNotFound(*request);
        });
    }

    void ServerSetup::handleWebNotFound(AsyncWebServerRequest &request) {
        logger.warning(DnApp::Common::Strings::format(
            "HttpServer: page not found! URI: %s, method: %s",
            request.url().c_str(),
            request.methodToString()
        ));

        request.send(
            404,
            "text/plain",
            DnApp::Common::Strings::format(
                "File Not Found\n\nURI: %s\nMethod: %s\n",
                request.url().c_str(),
                request.methodToString()
            ).get()
        );
    }

    void ServerSetup::logServerHasStarted() {
        String message = "HTTP server has started, open http://";

        // todo: get rid of the global
        message += WiFi.localIP().toString();

        message += ":";
        message += port;
        message += " or http://";
        message += hostname;
        message += ".local:";
        message += port;
        message += " in a web browser :)";

        logger.info(message);
    }

    void ServerSetup::onLoop() {
        // do nothing
    }

    String ServerSetup::dataToString(
        const uint8_t *data,
        size_t dataLength
    ) const {
        String string;
        string.reserve(dataLength);

        for (size_t i = 0; i < dataLength; i++) {
            string += char(data[i]);
        }

        return string;
    }
}
