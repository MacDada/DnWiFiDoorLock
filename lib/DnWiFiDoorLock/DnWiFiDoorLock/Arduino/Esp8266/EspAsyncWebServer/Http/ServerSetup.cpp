#include "ServerSetup.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    ServerSetup::ServerSetup(
        ESP8266WiFiClass& wiFi,
        AsyncWebServer& server,
        const char* const hostname,
        const unsigned int port,
        DoorLockController& doorLockController,
        FurnaceController& furnaceController,
        ServoButtonController& servoButtonController,
        ServoController& servoController,
        Logger& logger
    ):
        server{server},
        hostname{hostname},
        port{port},
        doorLockController{doorLockController},
        furnaceController{furnaceController},
        servoButtonController{servoButtonController},
        servoController{servoController},
        logger{logger},
        wiFi{wiFi} {
    }

    void ServerSetup::onSetup() {
        setupRouting();

        server.begin();

        logServerHasStarted();
    }

    void ServerSetup::setupRouting() {
        server.on(PSTR("/"), HTTP_GET, [&](AsyncWebServerRequest* const request) {
            request->redirect(F("/furnace"));
        });

        // https://discord.com/channels/583251190591258624/742849025191051326/995832013405835316
        //
        // todo: can i get null here instead of the object? o.O
        server.on(PSTR("/doorlock"), HTTP_GET, [&](AsyncWebServerRequest* const request) {
            doorLockController.statusAction(*request);
        });

        server.on(PSTR("/doorlock/switch"), HTTP_POST, [&](AsyncWebServerRequest* const request) {
            doorLockController.switchAction(*request);
        });

        server.on(PSTR("/furnace"), HTTP_GET, [&](AsyncWebServerRequest* const request) {
            furnaceController.statusAction(*request);
        });

        server.on(PSTR("/furnace/switch"), HTTP_POST, [&](AsyncWebServerRequest* const request) {
            furnaceController.switchAction(*request);
        });

        server.on(PSTR("/api/furnace"), HTTP_GET, [&](AsyncWebServerRequest* const request) {
            furnaceController.apiGetAction(*request);
        });

        server.on(PSTR("/api/furnace"), HTTP_POST, [&](AsyncWebServerRequest* const request) {
            // ignore, we use the callback with request body
        }, nullptr, [&](
            AsyncWebServerRequest* request,
            uint8_t* bodyData,
            size_t bodyDataLength,
            size_t index,
            size_t total
        ) {
            String body = dataToString(bodyData, bodyDataLength);

            furnaceController.apiPostAction(*request, body);
        });

        server.on(PSTR("/modal.css"), HTTP_GET, [&](AsyncWebServerRequest* const request) {
            servoButtonController.modalCssAction(*request);
        });

        server.on(PSTR("/modal.js"), HTTP_GET, [&](AsyncWebServerRequest* const request) {
            servoButtonController.modalJsAction(*request);
        });

        server.on(PSTR("/ajax-form.js"), HTTP_GET, [&](AsyncWebServerRequest* const request) {
            servoButtonController.ajaxFormJsAction(*request);
        });

        server.on(PSTR("/input-number-buttons.js"), HTTP_GET, [&](AsyncWebServerRequest* const request) {
            servoButtonController.inputNumberButtonsJsAction(*request);
        });

        server.on(PSTR("/servo-button.js"), HTTP_GET, [&](AsyncWebServerRequest* const request) {
            servoButtonController.javascriptAction(*request);
        });

        server.on(PSTR("/servo-button.css"), HTTP_GET, [&](AsyncWebServerRequest* const request) {
            servoButtonController.cssAction(*request);
        });

        server.on(PSTR("/servo-button"), HTTP_POST, [&](AsyncWebServerRequest* const request) {
            servoButtonController.updateSettingsAction(*request);
        });

        server.on(PSTR("/servo-button"), HTTP_GET, [&](AsyncWebServerRequest* const request) {
            servoButtonController.showSettingsAction(*request);
        });

        server.on(PSTR("/servo"), HTTP_GET | HTTP_POST, [&](AsyncWebServerRequest* const request) {
            servoController.angleAction(*request);
        });

        server.onNotFound([&](AsyncWebServerRequest* const request) {
            handleWebNotFound(*request);
        });
    }

    void ServerSetup::handleWebNotFound(AsyncWebServerRequest &request) {
        logger.warning(DnApp::Common::Strings::format(
            PSTR("HttpServer: page not found! URI: %s, method: %s"),
            request.url().c_str(),
            request.methodToString()
        ));

        request.send(
            404,
            F("text/plain"),
            DnApp::Common::Strings::format(
                PSTR("File Not Found\n\nURI: %s\nMethod: %s\n"),
                request.url().c_str(),
                request.methodToString()
            ).get()
        );
    }

    void ServerSetup::logServerHasStarted() {
        String message{F("HTTP server has started, open http://")};

        message += wiFi.localIP().toString();

        message += F(":");
        message += port;
        message += F(" or http://");
        message += hostname;
        message += F(".local:");
        message += port;
        message += F(" in a web browser :)");

        logger.info(message);
    }

    void ServerSetup::onLoop() {
        // do nothing
    }

    String ServerSetup::dataToString(
        const uint8_t* data,
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
