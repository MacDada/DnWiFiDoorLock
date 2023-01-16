#include "FurnaceController.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    FurnaceController::FurnaceController(
        const DnWiFiDoorLock::Arduino::Hardware& hardware,
        DnWiFiDoorLock::Furnace& furnace,
        DnApp::Logger::Logger& logger
    ):
        hardware{hardware},
        furnace{furnace},
        logger{logger} {
    }

    void FurnaceController::statusAction(AsyncWebServerRequest& request) const {
        logger.info(PSTR("FurnaceController::statusAction()"));

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
                    </html>
                )"),
                furnace.isHeaterOn() ? PSTR("włączone!") : PSTR("wyłączone!"),
                furnace.isHeaterOn() ? PSTR("&#128293;") : PSTR("&#10060;"),
                furnace.isHeaterOn() ? PSTR("włączone!") : PSTR("wyłączone!"),
                uptime.getHours(),
                uptime.getRemainingMinutes(),
                uptime.getRemainingSeconds()
            ).get()
        );
    }

    void FurnaceController::switchAction(AsyncWebServerRequest& request) const {
        logger.info(PSTR("FurnaceController::switchAction()"));

        furnace.toggleHeater();

        redirect(request, F("/furnace"));
    }

    void FurnaceController::apiGetAction(AsyncWebServerRequest& request) const {
        logger.info(PSTR("FurnaceController::apiGetAction()"));

        request.send(
            HTTP_RESPONSE_STATUS_OK,
            HTTP_RESPONSE_CONTENT_TYPE_JSON,
            furnace.isHeaterOn() ? F("true") : F("false")
        );
    }

    void FurnaceController::apiPostAction(
        AsyncWebServerRequest& request,
        const String& body
    ) const {
        logger.info(PSTR("FurnaceController::apiPostAction()"));

        if (body.equals(F("ON"))) {
            furnace.turnOnHeater();
        } else if (body.equals(F("OFF"))) {
            furnace.turnOffHeater();
        } else {
            logger.warning(PSTR("FurnaceController::apiPostAction(): Invalid value response"));

            request.send(
                HTTP_RESPONSE_STATUS_BAD_REQUEST,
                HTTP_RESPONSE_CONTENT_TYPE_JSON,
                F("Invalid value")
            );

            return;
        }

        request.send(
            HTTP_RESPONSE_STATUS_ACCEPTED,
            HTTP_RESPONSE_CONTENT_TYPE_JSON,
            furnace.isHeaterOn() ? F("true") : F("false")
        );
    }
}
