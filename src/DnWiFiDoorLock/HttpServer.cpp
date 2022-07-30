#include "DnWiFiDoorLock/HttpServer.h"

namespace DnWiFiDoorLock {

    HttpServer::HttpServer(
        AsyncWebServer &server,
        const char *serverHostName,
        const unsigned int serverPort,
        DoorLockController &doorLockController,
        ServoController &servoController,
        Logger::ArduinoLogger &logger
    ):
        server(server),
        serverHostName(serverHostName),
        serverPort(serverPort),
        doorLockController(doorLockController),
        servoController(servoController),
        logger(logger) {
    }

    void HttpServer::handleWebNotFound(AsyncWebServerRequest *request) {
        String message = "File Not Found\n\n";
        message += "URI: ";
        message += request->url();
        message += "\nMethod: ";
        message += request->methodToString();
        message += "\n";

        request->send(404, "text/plain", message);
    }

    void HttpServer::onSetup() {
        // todo; figure out why it crashes when handling "long" requests
        server.on("/test", HTTP_GET, [](AsyncWebServerRequest *request) {
            // 1000 OK, 2000 crash
            auto end = millis() + 2000;

            while (end > millis()) {
                // just wait for the test
            }

            request->send(200, "text/plain", "It is OK :-)");
        });

        server.on("/", HTTP_GET, [&](AsyncWebServerRequest *request) {
            doorLockController.statusAction(request);
        });

        server.on("/switch", HTTP_POST, [&](AsyncWebServerRequest *request) {
            doorLockController.switchAction(request);
        });

        server.on("/servo", HTTP_GET | HTTP_POST, [&](AsyncWebServerRequest *request) {
            servoController.angleAction(*request);
        });

        server.onNotFound([&](AsyncWebServerRequest *request) {
            handleWebNotFound(request);
        });

        server.begin();

        logServerHasStarted();
    }

    void HttpServer::logServerHasStarted() {
        String logMessage = "HTTP server has started, open http://";

        // todo: get rid of the global
        logMessage += WiFi.localIP().toString().c_str();

        logMessage += ":";
        logMessage += serverPort;
        logMessage += " or http://";
        logMessage += serverHostName;
        logMessage += ".local:";
        logMessage += serverPort;
        logMessage += " in a web browser :)\n";

        logger.log(logMessage);
    }

    void HttpServer::onLoop() {
        // do nothing
    }

}
