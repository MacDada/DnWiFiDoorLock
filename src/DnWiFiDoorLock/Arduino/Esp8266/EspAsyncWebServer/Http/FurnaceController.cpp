#include "FurnaceController.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    FurnaceController::FurnaceController(
        const DnWiFiDoorLock::Arduino::Hardware &hardware,
        DnWiFiDoorLock::Furnace &furnace,
        DnWiFiDoorLock::Logger::Logger &logger
    ):
        hardware(hardware),
        furnace(furnace),
        logger(logger) {
    }

    void FurnaceController::statusAction(AsyncWebServerRequest &request) const {
        logger.log("FurnaceController::statusAction()");

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
                        <title>EspDoorLock: ogrzewanie: %s</title>
                        <style>
                            h1 {
                                font-size: 1000%%;
                                line-height: 0;
                            }
                        </style>
                    </head>
                    <body>
                        <form action="/furnace/switch" method="post">
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
                furnace.isHeaterOn() ? "włączone!" : "wyłączone!",
                furnace.isHeaterOn() ? "&#128293;" : "&#10060;",
                furnace.isHeaterOn() ? "włączone!" : "wyłączone!",
                uptime.getHours(),
                uptime.getRemainingMinutes(),
                uptime.getRemainingSeconds()
            ).get()
        );
    }

    void FurnaceController::switchAction(AsyncWebServerRequest &request) const {
        logger.log("FurnaceController::switchAction()");

        furnace.switchHeater();

        redirect(request, "/furnace");
    }

    void FurnaceController::apiAction(AsyncWebServerRequest &request) const {
        logger.log("FurnaceController::apiAction()");

        if (isRequestMethodPost(request)) {
            // todo: ON/OFF instead of switch
            furnace.switchHeater();
        }

        request.send(
            HTTP_RESPONSE_STATUS_OK,
            HTTP_RESPONSE_CONTENT_TYPE_JSON,
            furnace.isHeaterOn() ? "true" : "false"
        );
    }

}
