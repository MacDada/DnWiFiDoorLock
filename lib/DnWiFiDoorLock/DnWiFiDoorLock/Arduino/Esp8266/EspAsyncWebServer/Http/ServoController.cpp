#include "ServoController.h"

namespace {
    using DnApp::Common::Strings::format;
}

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    ServoController::ServoController(
        Servo& servo,
        Logger& logger,
        const char* const appName
    ):
        servo{servo},
        logger{logger},
        appName{appName} {
    }

    void ServoController::angleAction(Request& request) {
        int oldAngle = servo.getAngle();

        auto maybeNewAngle = getRequestPostParameter(request, "angle");

        if (!maybeNewAngle) {
            showCurrentAngleResponse(request, oldAngle);

            return;
        }

        int newAngle = maybeNewAngle->toInt();

        if (!isValidAngle(newAngle)) {
            invalidAngleGivenResponse(request, oldAngle, newAngle);

            return;
        }

        servo.setAngle(newAngle);

        newAngleSetResponse(request, oldAngle, newAngle);
    }

    bool ServoController::isValidAngle(const int angle) const {
        return angle >= Servo::MIN_ANGLE && angle <= Servo::MAX_ANGLE;
    }

    void ServoController::newAngleSetResponse(
        Request& request,
        const int oldAngle,
        const int newAngle
    ) {
        logger.info(format(
            PSTR("ServoController: new angle was set: \"%d\""),
            newAngle
        ));

        request.send(
            HTTP_RESPONSE_STATUS_ACCEPTED,
            HTTP_RESPONSE_CONTENT_TYPE_HTML,
            renderAngleResponse(oldAngle, newAngle)
        );
    }

    void ServoController::invalidAngleGivenResponse(
        Request& request,
        const int oldAngle,
        const int newAngle
    ) {
        logger.info(format(
            PSTR("ServoController: invalid angle given: \"%d\""),
            newAngle
        ));

        request.send(
            HTTP_RESPONSE_STATUS_BAD_REQUEST,
            HTTP_RESPONSE_CONTENT_TYPE_HTML,
            renderAngleResponse(oldAngle, newAngle, true)
        );
    }

    void ServoController::showCurrentAngleResponse(
        Request& request,
        const int oldAngle
    ) {
        logger.info(format(
            PSTR("ServoController: showing current angle: \"%d\""),
            oldAngle
        ));

        request.send(
            HTTP_RESPONSE_STATUS_OK,
            HTTP_RESPONSE_CONTENT_TYPE_HTML,
            renderAngleResponse(oldAngle)
        );
    }

    String ServoController::renderAngleResponse(
        const int oldAngle,
        const std::optional<int> newAngle,
        const bool invalidAngle
    ) const {
        // todo: extract some kind of templates?
        //       or use a template engine?
        //       https://techtutorialsx.com/2021/09/08/esp32-json/
        // todo: for some reason, when I hit enter from the number input, two values are sent:
        //       zero and the input value -> causing the value to be zero after all
        //       it works ok when I click submit instead of hitting enter
        String content = F(R"(
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
        )");

        content.replace(F("{{ app_name }}"), appName);

        content.replace(F("{{ servo_min_angle }}"), String(Servo::MIN_ANGLE));
        content.replace(F("{{ servo_max_angle }}"), String(Servo::MAX_ANGLE));

        content.replace(
            F("{{ invalid_angle_error }}"),
            invalidAngle ? F("<p>ERROR: INVALID ANGLE!</p>") : F("")
        );

        content.replace(F("{{ old_or_current }}"), newAngle ? F("Old") : F("Current"));
        content.replace(F("{{ old_angle }}"), String(oldAngle));

        content.replace(
            F("{{ new_angle }}"),
            newAngle ? format(PSTR("<p>New angle: %d</p>"), newAngle.value()).get() : ""
        );

        content.replace(
            F("{{ angle_form_value }}"),
            String(newAngle ? newAngle.value() : oldAngle)
        );

        content.trim();

        return content;
    }
}
