#include "DnHttpServer.h"

using namespace DnWiFiDoorLock;

DnHttpServer::DnHttpServer(
    AsyncWebServer &server,
    const char *serverHostName,
    const unsigned int serverPort,
    DnHttpController &doorLockController
):
    server(&server),
    serverHostName(serverHostName),
    serverPort(serverPort),
    doorLockController(&doorLockController) {}

void DnHttpServer::handleWebNotFound(AsyncWebServerRequest *request) {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += request->url();
    message += "\nMethod: ";
    message += request->methodToString();
    message += "\n";

    request->send(404, "text/plain", message);
}

void DnHttpServer::start() {
    const bool mdnsHasStarted = (bool) MDNS.begin(serverHostName);

    if (mdnsHasStarted) {
        // todo: inject serial?
        Serial.println("MDNS responder started");
    } else {
        // todo: better error handling
        Serial.println("There was a problem to start MDNS!");
    }

    server->on("/", HTTP_GET, [&](AsyncWebServerRequest *request) {
        doorLockController->statusAction(request);
    });

    server->on("/switch", HTTP_POST, [&](AsyncWebServerRequest *request) {
        doorLockController->switchAction(request);
    });

    server->onNotFound([&](AsyncWebServerRequest *request) {
        handleWebNotFound(request);
    });

    server->begin();

    Serial.printf(
        "Web server started, open http://%s:%i",
        WiFi.localIP().toString().c_str(),
        serverPort
    );

    if (mdnsHasStarted) {
        Serial.printf(
            " or http://%s.local:%i",
            serverHostName,
            serverPort
        );
    }

    Serial.print(" in a web browser :)\n");
}

void DnHttpServer::handleRequests() {
    MDNS.update();
}
