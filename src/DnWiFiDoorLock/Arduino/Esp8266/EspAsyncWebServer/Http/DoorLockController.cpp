#include "DoorLockController.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    DoorLockController::DoorLockController(
        const DnWiFiDoorLock::Arduino::Hardware &hardware,
        DnWiFiDoorLock::Arduino::DoorLock &doorLock,
        DnWiFiDoorLock::Logger::Logger &logger
    ):
        hardware(hardware),
        doorLock(doorLock),
        logger(logger) {
    }

    void DoorLockController::statusAction(AsyncWebServerRequest &request) {
        logger.log("DoorLockController::statusAction()");

        Time uptime = hardware.getUptime();

        request.send(
            HTTP_RESPONSE_STATUS_OK,
            HTTP_RESPONSE_CONTENT_TYPE_HTML,
            Tools::format(
                // `PSTR()` loads string from Flash memory, instead of RAM
                // todo: does that mean it is slower, so should not use if enough memory?
                PSTR(
                    R"(<!DOCTYPE html>
                    <html>
                    <head>
                        <meta charset="utf-8">
                        <title>EspDoorLock: %s</title>
                        <style>
                            h1 {
                                font-size: 1000%%;
                                line-height: 0;
                            }
                        </style>
                    </head>
                    <body>
                        <form action="/switch" method="post">
                            <center>
                                <button type="submit">
                                    <h1>%s</h1>
                                    <h2>%s</h2>
                                </button>
                                <p>Uptime: %02dh:%02dm:%02ds</p>
                            </center>
                        </form>
                    </body>
                    </html>)"
                ),
                doorLock.isClosed() ? "zamknięte!" : "otwarte!",
                doorLock.isClosed() ? "&#128274;" : "&#128275;",
                doorLock.isClosed() ? "Zamknięte!" : "Otwarte!",
                uptime.getHours(),
                uptime.getRemainingMinutes(),
                uptime.getRemainingSeconds()
            ).get()
        );
    }

    void DoorLockController::switchAction(AsyncWebServerRequest &request) {
        logger.log("DoorLockController::switchAction()");

        doorLock.switchOpenClose();

        // request->redirect("/") is wrong as it sends 302
        AsyncWebServerResponse *const response = request.beginResponse(HTTP_RESPONSE_STATUS_REDIRECT);
        response->addHeader("Location", "/");
        request.send(response);
    }

}
