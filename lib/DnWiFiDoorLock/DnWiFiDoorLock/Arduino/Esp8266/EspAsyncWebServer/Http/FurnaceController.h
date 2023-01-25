#pragma once

#include <ESPAsyncWebServer.h>
#include <WString.h>

#include "DnApp/Logger/Logger.h"
#include "DnApp/Common/Strings.h"
#include "DnApp/Hardware/Furnace.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/Controller.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    class FurnaceController final:
        public Controller {
    public:
        explicit
        FurnaceController(
            const DnWiFiDoorLock::Arduino::Hardware& hardware,
            DnApp::Hardware::Furnace& furnace,
            DnApp::Logger::Logger& logger
        ):
            hardware{hardware},
            furnace{furnace},
            logger{logger} {
        }

        void statusAction(AsyncWebServerRequest& request) const {
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

        void switchAction(AsyncWebServerRequest& request) const {
            logger.info(PSTR("FurnaceController::switchAction()"));

            furnace.toggleHeater();

            redirect(request, PSTR("/furnace"));
        }

        void apiGetAction(AsyncWebServerRequest& request) const {
            logger.info(PSTR("FurnaceController::apiGetAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_JSON,
                furnace.isHeaterOn() ? PSTR("true") : PSTR("false")
            );
        }

        void apiPostAction(
            AsyncWebServerRequest& request,
            const String& body
        ) const {
            logger.info(PSTR("FurnaceController::apiPostAction()"));

            if (body.equals(PSTR("ON"))) {
                furnace.turnOnHeater();
            } else if (body.equals(PSTR("OFF"))) {
                furnace.turnOffHeater();
            } else {
                logger.warning(PSTR(
                    "FurnaceController::apiPostAction(): Invalid value response"
                ));

                request.send(
                    HTTP_RESPONSE_STATUS_BAD_REQUEST,
                    HTTP_RESPONSE_CONTENT_TYPE_JSON,
                    PSTR("Invalid value")
                );

                return;
            }

            request.send(
                HTTP_RESPONSE_STATUS_ACCEPTED,
                HTTP_RESPONSE_CONTENT_TYPE_JSON,
                furnace.isHeaterOn() ? PSTR("true") : PSTR("false")
            );
        }
    private:
        const DnWiFiDoorLock::Arduino::Hardware& hardware;

        DnApp::Hardware::Furnace& furnace;

        DnApp::Logger::Logger& logger;
    };

    static_assert(!std::is_abstract<FurnaceController>());
}
