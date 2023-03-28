#pragma once

#include <ESPAsyncWebServer.h>
#include <WString.h>

#include "DnApp/Logger/Decorator/PrefixPostfixMessageLoggerDecorator.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/DoorLock.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/Controller.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    class DoorLockController final:
        public Controller {
    private:
        using PrefixingLogger = DnApp
            ::Logger
            ::Decorator
            ::PrefixPostfixMessageLoggerDecorator;
    public:
        explicit
        DoorLockController(
            const DnWiFiDoorLock::Arduino::Hardware& hardware,
            DnWiFiDoorLock::Arduino::DoorLock& doorLock,
            DnApp::Logger::Logger& logger
        ):
            hardware{hardware},
            doorLock{doorLock},
            logger{PrefixingLogger{logger, PSTR("DoorLockController::")}} {
        }

        auto statusAction(AsyncWebServerRequest& request) const -> void {
            logger.info(PSTR("statusAction()"));

            auto uptime = hardware.getUptime();

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

        auto switchAction(AsyncWebServerRequest& request) -> void {
            logger.info(PSTR("switchAction()"));

            doorLock.switchOpenClose();

            // todo: route generator
            redirect(request, PSTR("/doorlock"));
        }
    private:
        const DnWiFiDoorLock::Arduino::Hardware& hardware;

        DnWiFiDoorLock::Arduino::DoorLock& doorLock;

        mutable
        PrefixingLogger logger;
    };

    static_assert(!std::is_abstract<DoorLockController>());
}
