#include "ServoController.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {

    ServoController::ServoController(
        Servo &servo,
        Logger::Logger &logger
    ):
        servo(servo),
        logger(logger) {
    }

    void ServoController::angleAction(Request &request) {
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

    bool ServoController::isValidAngle(int angle) const {
        return angle >= Servo::MIN_ANGLE && angle <= Servo::MAX_ANGLE;
    }

    void ServoController::newAngleSetResponse(Request &request, int oldAngle, int newAngle) {
        // todo: logger could accept the smart pointer directly
        logger.log(Tools::format(
            "ServoController: new angle was set: \"%d\"",
            newAngle
        ).get());

        request.send(
            HTTP_RESPONSE_STATUS_ACCEPTED,
            HTTP_RESPONSE_CONTENT_TYPE_HTML,
            renderAngleResponse(oldAngle, newAngle)
        );
    }

    void ServoController::invalidAngleGivenResponse(Request &request, int oldAngle, int newAngle) {
        logger.log(Tools::format(
            "ServoController: invalid angle given: \"%d\"",
            newAngle
        ).get());

        request.send(
            HTTP_RESPONSE_STATUS_BAD_REQUEST,
            HTTP_RESPONSE_CONTENT_TYPE_HTML,
            renderAngleResponse(oldAngle, newAngle, true)
        );
    }

    void ServoController::showCurrentAngleResponse(Request &request, int oldAngle) {
        logger.log(Tools::format(
            "ServoController: showing current angle: \"%d\"",
            oldAngle
        ).get());

        request.send(
            HTTP_RESPONSE_STATUS_OK,
            HTTP_RESPONSE_CONTENT_TYPE_HTML,
            renderAngleResponse(oldAngle)
        );
    }

    String ServoController::renderAngleResponse(
        int oldAngle,
        std::optional<int> newAngle,
        bool invalidAngle
    ) const {
        // todo: extract some kind of templates?
        //       or use a template engine?
        //       https://techtutorialsx.com/2021/09/08/esp32-json/
        // todo: would PSTR() or F() help in any way?
        // todo: for some reason, when I hit enter from the number input, two values are sent:
        //       zero and the input value -> causing the value to be zero after all
        //       it works ok when I click submit instead of hitting enter
        String content = R"(
            <!DOCTYPE html>
            <html>
                <head>
                    <meta charset="utf-8">
                    <title>Servo :: DnWiFiDoorLock</title>
                </head>
                <body>
                    <h1>DnWiFiDoorLock</h1>

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
        )";

        content.replace("{{ servo_min_angle }}", String(Servo::MIN_ANGLE));
        content.replace("{{ servo_max_angle }}", String(Servo::MAX_ANGLE));

        content.replace("{{ invalid_angle_error }}", invalidAngle ? "<p>ERROR: INVALID ANGLE!</p>" : "");

        content.replace("{{ old_or_current }}", newAngle ? "Old" : "Current");
        content.replace("{{ old_angle }}", String(oldAngle));

        content.replace("{{ new_angle }}", newAngle ? Tools::format("<p>New angle: %d</p>", newAngle.value()).get() : "");

        content.replace("{{ angle_form_value }}", String(newAngle ? newAngle.value() : oldAngle));

        content.trim();

        return content;
    }

    std::optional<String> ServoController::getRequestPostParameter(
        Request &request,
        const char *parameterName
    ) const {
        return request.hasParam(parameterName, true)
               ? request.getParam(parameterName, true)->value()
               : std::optional<String>{};
    }

}
