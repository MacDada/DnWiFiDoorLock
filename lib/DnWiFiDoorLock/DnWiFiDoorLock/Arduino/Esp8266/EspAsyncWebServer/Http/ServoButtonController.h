#pragma once

#include "ArduinoJson.h"
#include "ESPAsyncWebServer.h"
#include <WString.h>
#include <tl_expected>

#include "DnApp/Arduino/Logger/Decorator/PrefixPostfixMessageLoggerDecorator.h"
#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Common/Strings.h"
#include "DnApp/Hardware/Servo.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/Controller.h"
#include "DnWiFiDoorLock/Arduino/Servo/Button.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    /**
     * RAM issues forced me to split web content into multiple "resources"
     * – each served independently takes up less RAM per request.
     */
    class ServoButtonController final:
        public Controller {
    private:
        using Button = DnWiFiDoorLock::Arduino::Servo::Button;

        using LoggerDecorator = DnApp
            ::Arduino
            ::Logger
            ::Decorator
            ::PrefixPostfixMessageLoggerDecorator;
    public:
        explicit
        ServoButtonController(
            const char* const appName,
            Button& button,
            DnApp::Arduino::Logger::WithArduinoStringLogger& logger
        ):
            appName{appName},
            button{button},
            logger{LoggerDecorator{logger, PSTR("ServoButtonController: ")}} {
        };

        auto showSettingsAction(AsyncWebServerRequest& request) const -> void {
            logger.info(PSTR("showSettingsAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_HTML,
                renderSettingsFormPage()
            );
        }

        auto updateSettingsAction(AsyncWebServerRequest& request) -> void {
            logger.info(PSTR("updateSettingsAction()"));

            const auto settings = validateForm(request);

            if (!settings.has_value()) {
                jsonClientErrorResponse(request, settings.error().c_str());

                return;
            }

            handleValidSettings(request, settings.value());
        }

        // todo: include file as a string literal?
        //       https://forum.arduino.cc/t/how-to-store-a-file-in-code-memory/1075563/5
        auto cssAction(AsyncWebServerRequest& request) const -> void {
            logger.info(PSTR("cssAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_CSS,
                // language=CSS
                PSTR(R"(
                    body {
                        text-align: center;
                    }

                    form {
                        display: flex;
                        flex-flow: wrap;
                        justify-content: center;
                    }

                    fieldset {
                        margin: 1em;
                        padding: 1em;
                    }

                    legend {
                        padding-inline: 1em;
                    }

                    .buttons-container {
                        display: flex;
                        margin: 1em;
                        justify-content: center;
                    }

                    .buttons-container button {
                        display: block;
                        width: 100%;
                    }
                )")
            );
        }

        auto modalCssAction(AsyncWebServerRequest& request) const -> void {
            logger.info(PSTR("modalCssAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_CSS,
                // language=CSS
                PSTR(R"(
                    #modal-overlay {
                        position: fixed;
                        top: 0;
                        left: 0;
                        width: 100%;
                        height: 100%;
                        background: rgba(255, 255, 255, 0.6);
                        display: none; /* change to flex when visible */
                        justify-content: center;
                        align-items: center;
                    }

                    #modal-overlay.visible {
                        display: flex;
                    }

                    #modal-window {
                        background: white;
                        padding: 2em;
                        box-shadow: gray 0 0 3em 3em;
                        border-radius: 1em;
                        display: flex;
                        justify-content: center;
                        align-items: center;
                        min-width: 10%;
                        min-height: 10%;
                    }

                    @keyframes modal-box-shadow-blinker {
                        0% { box-shadow: grey 0 0 3em 3em }
                        50% { box-shadow: grey 0 0 2em 2em }
                        100% { box-shadow: grey 0 0 3em 3em }
                    }

                    #modal-window.blinking {
                        animation:
                            modal-box-shadow-blinker
                            1s
                            cubic-bezier(0.17, -0.29, 0.69, 1.12)
                            infinite;
                    }

                    #modal-content pre {
                        text-align: left;
                    }
                )")
            );
        }

        auto modalJsAction(AsyncWebServerRequest& request) const -> void {
            logger.info(PSTR("modalJsAction()"));

            // todo: extract to "statically" served file: LittleFS
            //       * https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html
            //       * https://microcontrollerslab.com/esp8266-nodemcu-web-server-using-littlefs-flash-file-system/
            //       * https://randomnerdtutorials.com/esp32-vs-code-platformio-spiffs/
            // todo: js minify before upload
            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_JAVASCRIPT,
                // language=JavaScript
                PSTR(R"(
                    const overlay = document.createElement('div');
                    overlay.id = 'modal-overlay';

                    const window = document.createElement('div');
                    window.id = 'modal-window';

                    const content = document.createElement('div');
                    content.id = 'modal-content';

                    document
                        .querySelector('body')
                        .appendChild(overlay);
                    overlay.appendChild(window);
                    window.appendChild(content);

                    export const modal = {
                        setHtmlContent: function (html) {
                            content.innerHTML = html;

                            return this;
                        },
                        show: function () {
                            overlay.classList.add('visible');

                            return this;
                        },
                        hide: function () {
                            overlay.classList.remove('visible');

                            return this;
                        },
                        isVisible: function () {
                            return overlay.classList.contains('visible');
                        },
                        setBlinking: function () {
                            window.classList.add('blinking');

                            return this;
                        },
                        setNotBlinking: function () {
                            window.classList.remove('blinking');

                            return this;
                        },
                        setLoadingScreen: function () {
                            return this
                                .setHtmlContent('Loading…')
                                .setBlinking()
                                .show();
                        }
                    };
                )")
            );
        }

        auto inputNumberButtonsJsAction(AsyncWebServerRequest& request) const -> void {
            logger.info(PSTR("inputNumberButtonsJsAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_JAVASCRIPT,
                // language=JavaScript
                PSTR(R"(
                    function addButtonsContainer(angleNumberInput) {
                        const buttonsContainer = document.createElement('div');
                        buttonsContainer.classList.add('buttons-container');

                        angleNumberInput.insertAdjacentElement(
                            'beforebegin',
                            buttonsContainer
                        );

                        return buttonsContainer;
                    }

                    function addButtonsColumn(buttonsContainer) {
                        let buttonsColumn = document.createElement('div');
                        buttonsColumn.classList.add('buttons-column');

                        buttonsContainer.appendChild(buttonsColumn);

                        return buttonsColumn;
                    }

                    function addButton(numberInput, value, container, formatValue) {
                        const name = numberInput.name;

                        const button = document.createElement('button');
                        button.type = 'submit';
                        button.name = name;
                        button.value = value.toString();
                        button.innerText = formatValue(value);

                        button.addEventListener('click', function () {
                            numberInput.value = this.value;
                        });

                        container.appendChild(button);
                    }

                    export function addButtons(numberInput, formatValue) {
                        const minValue = parseInt(numberInput.min);
                        const maxValue = parseInt(numberInput.max);
                        const step = parseInt(numberInput.dataset.buttonsStep);

                        const buttonsContainer = addButtonsContainer(numberInput);
                        const firstColumn = addButtonsColumn(buttonsContainer);
                        const secondColumn = addButtonsColumn(buttonsContainer);

                        let value = minValue;

                        do {
                            const column = value < (maxValue - minValue) / 2
                                ? firstColumn
                                : secondColumn;

                            addButton(numberInput, value, column, formatValue);

                            value += step;
                        } while (value < maxValue);

                        addButton(numberInput, maxValue, secondColumn, formatValue);
                    }
                )")
            );
        }

        auto ajaxFormJsAction(AsyncWebServerRequest& request) const -> void {
            logger.info(PSTR("ajaxFormJsAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_JAVASCRIPT,
                // language=JavaScript
                PSTR(R"(
                    import {modal} from './modal.js';

                    export function ajaxForm(form, onResponseData) {
                        form.addEventListener('submit', (event) => {
                            event.preventDefault();

                            modal.setLoadingScreen();

                            fetch(form.action, {
                                method: form.method,
                                body: new URLSearchParams(new FormData(form))
                            }).then((response) => {
                                if (!response.ok) {
                                    throw new Error('Server response was not OK!');
                                }

                                return response.json();
                            }).then((responseData) => {
                                modal.hide();

                                if (onResponseData) {
                                    onResponseData(responseData);
                                }
                            }).catch((error) => {
                                console.error('ajaxForm error: ', error);

                                modal
                                    .setNotBlinking()
                                    .setHtmlContent(`
                                        <h2>Error!</h2>
                                        <p>Unexpected problem occurred.</p>
                                        <p>You may want to try refreshing the page…</p>
                                    `)
                                    .show();
                            });
                        });
                    }
                )")
            );
        }

        auto javascriptAction(AsyncWebServerRequest& request) const -> void {
            logger.info(PSTR("javascriptAction()"));

            // todo: extract to "statically" served file? LittleFS
            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_JAVASCRIPT,
                // language=JavaScript
                PSTR(R"(
                    import { addButtons } from './input-number-buttons.js';
                    import { ajaxForm } from './ajax-form.js';

                    document
                        .querySelectorAll('input[name="pressing_angle"], input[name="not_pressing_angle"]')
                        .forEach((input) => addButtons(input, (value) => 'angle ' + value));

                    document
                        .querySelectorAll('input[name="pressing_milliseconds"]')
                        .forEach((input) => addButtons(input, (value) => value + ' ms'));

                    ajaxForm(document.getElementById('servo-button-form'), (responseData) => {
                        const settings = responseData.servo_button;

                        document.querySelector('.pressing-angle-value').textContent = settings.pressing_angle;
                        document.querySelector('.not-pressing-angle-value').textContent = settings.not_pressing_angle;
                        document.querySelector('.pressing-milliseconds-value').textContent = settings.pressing_milliseconds;
                    });
                )")
            );
        }
    private:
        using Servo = DnApp::Hardware::Servo;

        struct Settings final {
            const Servo::Angle pressingAngle;

            const Servo::Angle notPressingAngle;

            const Button::PressingMilliseconds pressingMilliseconds;
        };

        static
        constexpr
        const
        auto format = DnApp::Common::Strings::format;

        const char* const appName;

        Button& button;

        mutable
        LoggerDecorator logger;

        auto renderSettingsFormPage() const -> String {
            logger.info(PSTR("renderSettingsFormPage(): generating pageContent"));

            // todo: maybe extract SettingsView
            // language=HTML
            auto page = String{PSTR(R"(
                <!DOCTYPE html>
                <html>
                    <head>
                        <meta charset="utf-8">

                        <title>{{ button_name }} :: ServoButton :: {{ app_name }}</title>

                        <meta name="viewport" content="width=device-width, initial-scale=1">

                        <link rel="stylesheet" href="/modal.css">
                        <link rel="stylesheet" href="/servo-button.css">

                        <script type="module" src="/servo-button.js"></script>
                    </head>
                    <body>
                        <h1>{{ app_name }}</h1>

                        <h2>ServoButton: <em>{{ button_name }}</em></h2>

                        <form id="servo-button-form" action="/servo-button" method="post">
                            <fieldset>
                                <legend>
                                    Pressing angle:

                                    <span class="pressing-angle-value">
                                        {{ pressing_angle }}
                                    </span>
                                </legend>

                                <input
                                    type="number"
                                    min="{{ servo_min_angle }}"
                                    max="{{ servo_max_angle }}"
                                    data-buttons-step="10"
                                    name="pressing_angle"
                                    value="{{ pressing_angle }}"
                                >

                                <input type="submit">
                            </fieldset>

                            <fieldset>
                                <legend>
                                    Not pressing angle:

                                    <span class="not-pressing-angle-value">
                                        {{ not_pressing_angle }}
                                    </span>
                                </legend>

                                <input
                                    type="number"
                                    min="{{ servo_min_angle }}"
                                    max="{{ servo_max_angle }}"
                                    data-buttons-step="10"
                                    name="not_pressing_angle"
                                    value="{{ not_pressing_angle }}"
                                >

                                <input type="submit">
                            </fieldset>

                            <fieldset>
                                <legend>
                                    Pressing milliseconds:

                                    <span class="pressing-milliseconds-value">
                                        {{ pressing_milliseconds }}
                                    </span>
                                </legend>

                                <input
                                    type="number"
                                    min="{{ min_pressing_milliseconds }}"
                                    max="{{ max_pressing_milliseconds }}"
                                    step="100"
                                    data-buttons-step="100"
                                    name="pressing_milliseconds"
                                    value="{{ pressing_milliseconds }}"
                                >

                                <input type="submit">
                            </fieldset>
                        </form>
                    </body>
                </html>
            )")};

            page.replace(PSTR("{{ app_name }}"), appName);
            page.replace(PSTR("{{ button_name }}"), PSTR("Heater"));
            page.replace(PSTR("{{ servo_min_angle }}"), String{Servo::Angle::MIN});
            page.replace(PSTR("{{ servo_max_angle }}"), String{Servo::Angle::MAX});
            page.replace(PSTR("{{ pressing_angle }}"), String{button.getPressingAngle().getDegrees()});
            page.replace(PSTR("{{ not_pressing_angle }}"), String{button.getNotPressingAngle().getDegrees()});
            page.replace(PSTR("{{ pressing_milliseconds }}"), String{button.getPressingMilliseconds().getValue()});
            page.replace(PSTR("{{ min_pressing_milliseconds }}"), String{
                Button::PressingMilliseconds::create(100).value().getValue()
            });
            page.replace(PSTR("{{ max_pressing_milliseconds }}"), String{
                Button::PressingMilliseconds::create(5000).value().getValue()
            });

            // todo: extract render() after all? ;-)
            // #include <tuple>
//            for (auto const& [find, replace] : std::vector<std::tuple<const String, const String>>{
//                {PSTR("{{ app_name }}"), PSTR("Furnace")},
//                {PSTR("{{ pressing_milliseconds }}"), String(button.getPressingMilliseconds())}
//            }) {
//                page.replace(find, replace);
//            }

            return page;
        }

        auto validateForm(AsyncWebServerRequest& request) const -> tl::expected<Settings, String> {
            const auto maybeNewPressingAngle = getRequestPostParameter(request, PSTR("pressing_angle"));
            const auto maybeNewNotPressingAngle = getRequestPostParameter(request, PSTR("not_pressing_angle"));
            const auto maybeNewMilliseconds = getRequestPostParameter(request, PSTR("pressing_milliseconds"));

            if (!maybeNewPressingAngle
                || !maybeNewNotPressingAngle
                || !maybeNewMilliseconds
            ) {
                return tl::unexpected{PSTR("No required data given")};
            }

            // todo: what if a negative number was given?
            const auto newPressingAngle = Servo::Angle::withDegrees(maybeNewPressingAngle->toInt());
            const auto newNotPressingAngle = Servo::Angle::withDegrees(maybeNewNotPressingAngle->toInt());
            const auto newMilliseconds = Button::PressingMilliseconds::create(maybeNewMilliseconds->toInt());

            if (!newPressingAngle) {
                return tl::unexpected{PSTR("Invalid pressing angle")};
            }

            if (!newNotPressingAngle) {
                return tl::unexpected{PSTR("Invalid not pressing angle")};
            }

            if (!newMilliseconds) {
                return tl::unexpected{
                    String{PSTR("Invalid pressing milliseconds: ")} + newMilliseconds.error()
                };
            }

            return Settings{
                *newPressingAngle,
                *newNotPressingAngle,
                newMilliseconds.value()
            };
        }

        auto handleValidSettings(
            AsyncWebServerRequest& request,
            const Settings& settings
        ) -> void {
            button.setPressingAngle(settings.pressingAngle);
            button.setNotPressingAngle(settings.notPressingAngle);
            button.setPressingMilliseconds(settings.pressingMilliseconds);

            logger.info(PSTR("Updated settings"));

            servoButtonJsonResponse(request);
        }

        auto servoButtonJsonResponse(AsyncWebServerRequest& request) const -> void {
            auto json = StaticJsonDocument<
                // https://arduinojson.org/v6/assistant/
                //   Data structures: 64
                //   Strings: 69
                //   Total (minimum): 133
                //   Total (recommended): 192
                192
            >{};

            json[F("servo_button")][F("pressing_angle")] = button.getPressingAngle().getDegrees();
            json[F("servo_button")][F("not_pressing_angle")] = button.getNotPressingAngle().getDegrees();
            json[F("servo_button")][F("pressing_milliseconds")] = button.getPressingMilliseconds().getValue();

            jsonSuccessResponse(request, json);
        }

        auto jsonSuccessResponse(
            AsyncWebServerRequest& request,
            const JsonDocument& json
        ) const -> void {
            if (json.overflowed()) {
                jsonOverflowedErrorResponse(request);

                return;
            }

            auto* response = request.beginResponseStream(
                HTTP_RESPONSE_CONTENT_TYPE_JSON
            );

            serializeJson(json, *response);

            request.send(response);
        }

        auto jsonClientErrorResponse(
            AsyncWebServerRequest& request,
            const char* const error
        ) const -> void {
            logger.warning(format(
                PSTR("Client error: %s"),
                error
            ));

            const auto errorKey = String{F("error")};

            auto json = DynamicJsonDocument{
                // https://arduinojson.org/v6/assistant/
                JSON_OBJECT_SIZE(1) + errorKey.length()
            };

            json[errorKey] = error;

            if (json.overflowed()) {
                jsonOverflowedErrorResponse(request);

                return;
            }

            auto* response = request.beginResponseStream(
                HTTP_RESPONSE_CONTENT_TYPE_JSON
            );
            response->setCode(HTTP_RESPONSE_STATUS_BAD_REQUEST);

            serializeJson(json, *response);

            request.send(response);
        }

        auto jsonOverflowedErrorResponse(
            AsyncWebServerRequest& request
        ) const -> void {
            internalServerErrorResponse(
                request,
                PSTR("JsonDocument overflowed")
            );
        }

        auto internalServerErrorResponse(
            AsyncWebServerRequest& request,
            const char* const error
        ) const -> void {
            logger.error(error);

            request.send(
                HTTP_RESPONSE_STATUS_INTERNAL_SERVER_ERROR,
                HTTP_RESPONSE_CONTENT_TYPE_PLAIN,
                PSTR("Error 500: Internal Server Error")
            );
        }
    };

    static_assert(!std::is_abstract<ServoButtonController>());
}
