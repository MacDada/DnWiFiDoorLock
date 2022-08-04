#include "ServerSetup.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    ServerSetup::ServerSetup(
        AsyncWebServer &server,
        const char *const hostname,
        const unsigned int port,
        DoorLockController &doorLockController,
        ServoController &servoController,
        Logger &logger
    ):
        server(server),
        hostname(hostname),
        port(port),
        doorLockController(doorLockController),
        servoController(servoController),
        logger(logger) {
    }

    void ServerSetup::onSetup() {
        setupRouting();

        server.begin();

        logServerHasStarted();
    }

    void ServerSetup::setupRouting() {
        // https://discord.com/channels/583251190591258624/742849025191051326/995832013405835316
        //
        // todo: can i get null here instead of the object? o.O
        server.on("/", HTTP_GET, [&](AsyncWebServerRequest *const request) {
            doorLockController.statusAction(*request);
        });

        server.on("/switch", HTTP_POST, [&](AsyncWebServerRequest *const request) {
            doorLockController.switchAction(*request);
        });

        server.on("/servo", HTTP_GET | HTTP_POST, [&](AsyncWebServerRequest *const request) {
            servoController.angleAction(*request);
        });

        server.onNotFound([&](AsyncWebServerRequest *const request) {
            handleWebNotFound(*request);
        });
    }

    void ServerSetup::handleWebNotFound(AsyncWebServerRequest &request) {
        logger.log(Tools::format(
            "HttpServer: page not found! URI: %s, method: %s",
            request.url().c_str(),
            request.methodToString()
        ));

        request.send(
            404,
            "text/plain",
            Tools::format(
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

        logger.log(message);
    }

    void ServerSetup::onLoop() {
        // do nothing
    }

}
