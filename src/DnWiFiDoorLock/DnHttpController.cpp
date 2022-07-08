#include "DnHttpController.h"

using namespace DnWiFiDoorLock;

DnHttpController::DnHttpController(
    DnHardware &hardware,
    DnDoorLock &doorLock
) {
    this->hardware = &hardware;
    this->doorLock = &doorLock;
}

void DnHttpController::statusAction(ESP8266WebServer &server) {
    DnTime uptime = this->hardware->getUptime();

    server.send(
        HTTP_RESPONSE_STATUS_OK,
        HTTP_RESPONSE_CONTENT_TYPE_HTML,
        DnTools::format(
            // `PSTR()` loads string from Flash memory, instead of RAM
            // todo: does that mean it is slower, so should not use if enough memory?
            PSTR(
                "<!DOCTYPE html>\
                <html>\
                <head>\
                    <meta charset=\"utf-8\">\
                    <title>EspDoorLock: %s</title>\
                    <style>\
                        h1 {\
                            font-size: 1000%%;\
                            line-height: 0;\
                        }\
                    </style>\
                </head>\
                <body>\
                    <form action=\"/switch\" method=\"post\">\
                        <center>\
                            <button type=\"submit\">\
                                <h1>%s</h1>\
                                <h2>%s</h2>\
                            </button>\
                            <p>Uptime: %02dh:%02dm:%02ds</p>\
                        </center>\
                    </form>\
                </body>\
                </html>"
            ),
            doorLock->isClosed() ? "zamknięte!" : "otwarte!",
            doorLock->isClosed() ? "&#128274;" : "&#128275;",
            doorLock->isClosed() ? "Zamknięte!" : "Otwarte!",
            uptime.getHours(),
            uptime.getRemainingMinutes(),
            uptime.getRemainingSeconds()
        )
    );
}

void DnHttpController::switchAction(ESP8266WebServer &server) {
    if (server.method() != HTTP_POST) {
        server.send(
            HTTP_RESPONSE_STATUS_METHOD_NOT_ALLOWED,
            HTTP_RESPONSE_CONTENT_TYPE_PLAIN,
            "Method Not Allowed"
        );

        return;
    }

    doorLock->switchOpenClose();

    server.sendHeader("Location", "/", true);
    server.send(HTTP_RESPONSE_STATUS_REDIRECT);
}
