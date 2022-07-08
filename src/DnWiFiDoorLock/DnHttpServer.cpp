#include "DnHttpServer.h"

using namespace DnWiFiDoorLock;

DnHttpServer::DnHttpServer(
    ESP8266WebServer &server,
    const char *serverHostName,
    const unsigned int serverPort,
    DnHttpController &doorLockController
):
    server(&server),
    serverHostName(serverHostName),
    serverPort(serverPort),
    doorLockController(&doorLockController) {}

void DnHttpServer::handleWebNotFound() {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server->uri();
    message += "\nMethod: ";
    message += server->method() == HTTP_GET ? "GET" : "POST";
    message += "\nArguments: ";
    message += server->args();
    message += "\n";

    for (uint8_t i = 0; i < server->args(); i++) {
        message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
    }

    server->send(404, "text/plain", message);
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

    // todo: Request class
    // todo: Response class
    server->on("/", [&] {
        doorLockController->statusAction(*server);
    });

    server->on("/switch", [&] {
        doorLockController->switchAction(*server);
    });

    server->onNotFound([&] {
        handleWebNotFound();
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
    server->handleClient();

    MDNS.update();
}
