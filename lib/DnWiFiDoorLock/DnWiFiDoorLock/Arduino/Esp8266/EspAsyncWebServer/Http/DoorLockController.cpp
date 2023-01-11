#include "DoorLockController.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    DoorLockController::DoorLockController(
        const DnWiFiDoorLock::Arduino::Hardware &hardware,
        DnWiFiDoorLock::Arduino::DoorLock &doorLock,
        DnApp::Logger::Logger &logger
    ):
        hardware(hardware),
        doorLock(doorLock),
        logger(logger) {
    }

    void DoorLockController::statusAction(AsyncWebServerRequest &request) const {
        logger.info(PSTR("DoorLockController::statusAction()"));

        Time uptime = hardware.getUptime();

        request.send(
            HTTP_RESPONSE_STATUS_OK,
            HTTP_RESPONSE_CONTENT_TYPE_HTML,
            DnApp::Common::Strings::format(
                PSTR(R"(
                    <!DOCTYPE html>
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
                        <form action="/doorlock/switch" method="post">
                            <center>
                                <button type="submit">
                                    <h1>%s</h1>
                                    <h2>%s</h2>
                                </button>
                                <p>Uptime: %02dh:%02dm:%02ds</p>
                            </center>
                        </form>
                    </body>
                    </html>
                )"),
                doorLock.isClosed() ? PSTR("zamknięte!") : PSTR("otwarte!"),
                doorLock.isClosed() ? PSTR("&#128274;") : PSTR("&#128275;"),
                doorLock.isClosed() ? PSTR("Zamknięte!") : PSTR("Otwarte!"),
                uptime.getHours(),
                uptime.getRemainingMinutes(),
                uptime.getRemainingSeconds()
            ).get()
        );
    }

    void DoorLockController::switchAction(AsyncWebServerRequest &request) {
        logger.info(PSTR("DoorLockController::switchAction()"));

        doorLock.switchOpenClose();

        // todo: route generator
        redirect(request, F("/doorlock"));
    }
}
