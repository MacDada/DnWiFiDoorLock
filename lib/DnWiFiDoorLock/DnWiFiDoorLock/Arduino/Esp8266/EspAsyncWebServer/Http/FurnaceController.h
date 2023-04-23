#pragma once

#include <ESPAsyncWebServer.h>
#include <WString.h>

#include "DnApp/Arduino/Hardware/Board.h"
#include "DnApp/Common/Strings.h"
#include "DnApp/Hardware/Furnace.h"
#include "DnApp/Logger/Decorator/PrefixPostfixMessageLoggerDecorator.h"
#include "DnApp/Logger/Logger.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/Controller.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    class FurnaceController final:
        public Controller {
    private:
        using PrefixingLogger = DnApp
            ::Logger
            ::Decorator
            ::PrefixPostfixMessageLoggerDecorator;
    public:
        explicit
        FurnaceController(
            const DnApp::Arduino::Hardware::Board& board,
            DnApp::Hardware::Furnace& furnace,
            DnApp::Logger::Logger& logger
        ):
            board{board},
            furnace{furnace},
            logger{PrefixingLogger{logger, PSTR("FurnaceController::")}} {
        }

        auto statusAction(AsyncWebServerRequest& request) const -> void {
            logger.info(PSTR("statusAction()"));

            auto uptime = board.getUptime();

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
                    uptime.getMinutesRemainder(),
                    uptime.getSecondsRemainder()
                ).get()
            );
        }

        auto switchAction(AsyncWebServerRequest& request) -> void {
            logger.info(PSTR("switchAction()"));

            furnace.toggleHeater();

            redirect(request, PSTR("/furnace"));
        }

        auto apiGetAction(AsyncWebServerRequest& request) const -> void {
            logger.info(PSTR("apiGetAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_JSON,
                furnace.isHeaterOn() ? PSTR("true") : PSTR("false")
            );
        }

        auto apiPostAction(
            AsyncWebServerRequest& request,
            const String& body
        ) -> void {
            logger.info(PSTR("apiPostAction()"));

            // todo: why PSTR() does NOT work here?
            if (body.equals(F("ON"))) {
                furnace.turnOnHeater();
            } else if (body.equals(F("OFF"))) {
                furnace.turnOffHeater();
            } else {
                logger.warning(PSTR("apiPostAction(): Invalid value response"));

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
        const DnApp::Arduino::Hardware::Board& board;

        DnApp::Hardware::Furnace& furnace;

        mutable
        PrefixingLogger logger;
    };

    static_assert(!std::is_abstract<FurnaceController>());
}
