#pragma once

#include <optional>
#include <type_traits> // std::is_abstract

#include <ESPAsyncWebServer.h>
#include <WString.h>

#include "DnApp/Logger/Decorator/PrefixPostfixMessageLoggerDecorator.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Common/Strings.h"
#include "DnApp/Hardware/Servo.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/Controller.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    class ServoController final:
        public Controller {
    private:
        using Logger = DnApp::Logger::Logger;
        using Request = AsyncWebServerRequest;
        using PrefixingLogger = DnApp
            ::Logger
            ::Decorator
            ::PrefixPostfixMessageLoggerDecorator;
        using Servo = DnApp::Hardware::Servo;
    public:
        explicit
        ServoController(
            Servo& servo,
            Logger& logger,
            const char* const appName
        ):
            servo{servo},
            logger{PrefixingLogger{logger, PSTR("ServoController: ")}},
            appName{appName} {
        }

        auto angleAction(Request& request) -> void {
            auto oldAngle = servo.getAngle();

            auto maybeNewAngle = getRequestPostParameter(request, "angle");

            if (!maybeNewAngle) {
                showCurrentAngleResponse(request, oldAngle);

                return;
            }

            const auto newAngle = Servo::Angle::withDegrees((int) maybeNewAngle->toInt());

            if (!newAngle) {
                invalidAngleGivenResponse(request, oldAngle, *maybeNewAngle);

                return;
            }

            servo.setAngle(*newAngle);

            // todo: find/make something "safer" than std::optional
            //       the fact that dereferencing WITHOUT CHECKING FOR NULL
            //       is even possible makes std::optional UNSAFE
            //       (and also tempting to be used – it's just too easy xd)
            newAngleSetResponse(request, oldAngle, *newAngle);
        }
    private:
        Servo& servo;

        mutable
        PrefixingLogger logger;

        const char* const appName;

        static
        constexpr
        const
        auto format = DnApp::Common::Strings::format;

        auto newAngleSetResponse(
            Request& request,
            const int oldAngle,
            const Servo::Angle newAngle
        ) const -> void {
            logger.info(format(
                PSTR("New angle was set: %d°"),
                newAngle.getDegrees()
            ));

            request.send(
                HTTP_RESPONSE_STATUS_ACCEPTED,
                HTTP_RESPONSE_CONTENT_TYPE_HTML,
                renderAngleResponse(oldAngle, newAngle)
            );
        }

        auto invalidAngleGivenResponse(
            Request& request,
            const int oldAngle,
            const String& invalidAngle
        ) const -> void {
            logger.warning(format(
                PSTR("Invalid angle value given: \"%s\""),
                invalidAngle.c_str()
            ));

            request.send(
                HTTP_RESPONSE_STATUS_BAD_REQUEST,
                HTTP_RESPONSE_CONTENT_TYPE_HTML,
                renderAngleResponse(oldAngle, {}, true)
            );
        }

        auto showCurrentAngleResponse(
            Request& request,
            const int oldAngle
        ) const -> void {
            logger.info(format(
                PSTR("Showing current angle: \"%d\""),
                oldAngle
            ));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_HTML,
                renderAngleResponse(oldAngle)
            );
        }

        auto renderAngleResponse(
            const int oldAngle,
            const std::optional<Servo::Angle> newAngle = {},
            const bool invalidAngle = false
        ) const -> String {
            // todo: extract some kind of templates?
            //       or use a template engine?
            //       https://techtutorialsx.com/2021/09/08/esp32-json/
            // todo: for some reason, when I hit enter from the number input, two values are sent:
            //       zero and the input value -> causing the value to be zero after all
            //       it works ok when I click submit instead of hitting enter
            auto content = String{PSTR(R"(
                <!DOCTYPE html>
                <html>
                    <head>
                        <meta charset="utf-8">
                        <title>Servo :: {{ app_name }}</title>
                    </head>
                    <body>
                        <h1>{{ app_name }}</h1>

                        <h2>Servo</h2>

                        <p>{{ old_or_current }} angle: {{ old_angle }}</p>

                        {{ invalid_angle_error }}

                        {{ new_angle }}

                        <form action="/servo" method="post">
                            <button type="submit" name="angle" value="{{ servo_min_angle }}">
                                angle {{ servo_min_angle }}
                            </button>

                            <button type="submit" name="angle" value="90">
                                angle 90
                            </button>

                            <button type="submit" name="angle" value="{{ servo_max_angle }}">
                                angle {{ servo_max_angle }}
                            </button>

                            <input
                                type="number"
                                min="{{ servo_min_angle }}"
                                max="{{ servo_max_angle }}"
                                step="5"
                                name="angle"
                                value="{{ angle_form_value }}"
                                required
                            >

                            <input type="submit">
                        </form>
                    </body>
                </html>
            )")};

            content.replace(PSTR("{{ app_name }}"), appName);

            content.replace(PSTR("{{ servo_min_angle }}"), String{Servo::Angle::MIN});
            content.replace(PSTR("{{ servo_max_angle }}"), String{Servo::Angle::MAX});

            content.replace(
                PSTR("{{ invalid_angle_error }}"),
                invalidAngle ? PSTR("<p>ERROR: INVALID ANGLE!</p>") : PSTR("")
            );

            content.replace(PSTR("{{ old_or_current }}"), newAngle ? PSTR("Old") : PSTR("Current"));
            content.replace(PSTR("{{ old_angle }}"), String{oldAngle});

            content.replace(
                PSTR("{{ new_angle }}"),
                newAngle
                    ? format(
                        PSTR("<p>New angle: %d</p>"),
                        newAngle->getDegrees()
                    ).get()
                    : ""
            );

            content.replace(
                PSTR("{{ angle_form_value }}"),
                String(newAngle ? newAngle->getDegrees() : oldAngle)
            );

            content.trim();

            return content;
        }
    };

    static_assert(!std::is_abstract<ServoController>());
}
