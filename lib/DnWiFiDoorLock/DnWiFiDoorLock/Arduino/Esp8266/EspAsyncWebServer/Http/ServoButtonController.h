#pragma once

#include <variant>

#include "ESPAsyncWebServer.h"
#include <WString.h>

#include "DnApp/Arduino/Logger/Logger.h"
#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/Controller.h"
#include "DnWiFiDoorLock/Arduino/Servo/Button.h"
#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    /**
     * RAM issues forced me to split web content into multiple "resources"
     * – each served independently takes up less RAM per request.
     */
    class ServoButtonController final:
        public Controller {
    public:
        explicit ServoButtonController(
            const char *const appName,
            DnWiFiDoorLock::Arduino::Servo::Button &button,
            DnApp::Arduino::Logger::Logger &logger
        ):
            appName(appName),
            button(button),
            logger(logger) {
        };

        void showSettingsAction(AsyncWebServerRequest &request) {
            logger.info(F("ServoButtonController::showSettingsAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_HTML,
                renderSettingsFormPage()
            );
        }

        void updateSettingsAction(AsyncWebServerRequest &request) {
            logger.info(F("ServoButtonController::updateSettingsAction()"));

            auto settingsOrError = validateForm(request);

            // todo: maybe this could be simpler? I guess I could make a wrapper…
            //       https://discord.com/channels/583251190591258624/602633986061369344/1060277428624310312
            if (std::holds_alternative<SettingsError>(settingsOrError)) {
                clientErrorResponse(request, std::get<SettingsError>(settingsOrError));

                return;
            }

            handleValidSettings(
                request,
                std::get<Settings>(settingsOrError)
            );
        }

        // todo: include file as a string literal?
        //       https://forum.arduino.cc/t/how-to-store-a-file-in-code-memory/1075563/5
        void cssAction(AsyncWebServerRequest &request) {
            logger.info(F("ServoButtonController::cssAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_CSS,
                // language=CSS
                F(R"(
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

        void modalCssAction(AsyncWebServerRequest &request) {
            logger.info(F("ServoButtonController::modalCssAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_CSS,
                // language=CSS
                F(R"(
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

        void modalJsAction(AsyncWebServerRequest &request) {
            logger.info(F("ServoButtonController::modalJsAction()"));

            // todo: extract to "statically" served file: LittleFS
            // todo: js minify before upload
            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_JAVASCRIPT,
                // language=JavaScript
                F(R"(
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

        void inputNumberButtonsJsAction(AsyncWebServerRequest &request) {
            logger.info(F("ServoButtonController::inputNumberButtonsJsAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_JAVASCRIPT,
                // language=JavaScript
                F(R"(
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

        void ajaxFormJsAction(AsyncWebServerRequest &request) {
            logger.info(F("ServoButtonController::ajaxFormJsAction()"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_JAVASCRIPT,
                // language=JavaScript
                F(R"(
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

        void javascriptAction(AsyncWebServerRequest &request) {
            logger.info(F("ServoButtonController::javascriptAction()"));

            // todo: extract to "statically" served file? LittleFS
            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_JAVASCRIPT,
                // language=JavaScript
                F(R"(
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
        using Servo = DnWiFiDoorLock::Arduino::Servo::Servo;

        struct Settings final {
            const int pressingAngle;

            const int notPressingAngle;

            const int pressingMilliseconds;
        };

        using SettingsError = String;

        static
        constexpr
        auto format = DnApp::Common::Strings::format;

        // todo: change code style:
        //       the asterisk "belongs" to the "left" side after all xd
        const char *const appName;

        DnWiFiDoorLock::Arduino::Servo::Button &button;

        DnApp::Arduino::Logger::Logger &logger;

        String renderSettingsFormPage() const {
            // todo: make PrependMessageDecoratorLogger to stop repeating class' name
            logger.info(F(
                "ServoButtonController::renderSettingsFormPage(): generating pageContent"
            ));

            // todo: maybe extract SettingsView
            // language=HTML
            String page = F(R"(
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
                                    min="100"
                                    max="5000"
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
            )");

            page.replace(F("{{ app_name }}"), appName);
            page.replace(F("{{ button_name }}"), F("Heater"));
            page.replace(F("{{ servo_min_angle }}"), String(Servo::MIN_ANGLE));
            page.replace(F("{{ servo_max_angle }}"), String(Servo::MAX_ANGLE));
            page.replace(F("{{ pressing_angle }}"), String(button.getPressingAngle()));
            page.replace(F("{{ not_pressing_angle }}"), String(button.getNotPressingAngle()));
            page.replace(F("{{ pressing_milliseconds }}"), String(button.getPressingMilliseconds()));

            // todo: extract render() after all? ;-)
            // #include <tuple>
//            for (auto const& [find, replace] : std::vector<std::tuple<const String, const String>>{
//                {F("{{ app_name }}"), F("Furnace")},
//                {F("{{ pressing_milliseconds }}"), String(button.getPressingMilliseconds())}
//            }) {
//                page.replace(find, replace);
//            }

            return page;
        }

        std::variant<Settings, SettingsError> validateForm(AsyncWebServerRequest &request) const {
            auto maybeNewPressingAngle = getRequestPostParameter(request, PSTR("pressing_angle"));
            auto maybeNewNotPressingAngle = getRequestPostParameter(request, PSTR("not_pressing_angle"));
            auto maybeNewMilliseconds = getRequestPostParameter(request, PSTR("pressing_milliseconds"));

            if (!maybeNewPressingAngle
                || !maybeNewNotPressingAngle
                || !maybeNewMilliseconds
            ) {
                return F("No required data given");
            }

            int newPressingAngle = maybeNewPressingAngle->toInt();
            int newNotPressingAngle = maybeNewNotPressingAngle->toInt();
            int newMilliseconds = maybeNewMilliseconds->toInt();

            if (!isValidAngle(newPressingAngle)) {
                return F("Invalid pressing angle");
            }

            if (!isValidAngle(newNotPressingAngle)) {
                return F("Invalid not pressing angle");
            }

            if (newMilliseconds <= 0) {
                return F("Invalid pressing milliseconds");
            }

            return Settings{newPressingAngle, newNotPressingAngle, newMilliseconds};
        }

        void handleValidSettings(
            AsyncWebServerRequest &request,
            const Settings &settings
        ) {
            button.setPressingAngle(settings.pressingAngle);
            button.setNotPressingAngle(settings.notPressingAngle);
            button.setPressingMilliseconds(settings.pressingMilliseconds);

            logger.info(F("ServoButtonController: updated settings"));

            request.send(
                HTTP_RESPONSE_STATUS_OK,
                HTTP_RESPONSE_CONTENT_TYPE_JSON,
                format(
                    // todo: https://github.com/bblanchon/ArduinoJson/
                    // language=JSON
                    PSTR(R"({
                        "servo_button": {
                            "pressing_angle": %d,
                            "not_pressing_angle": %d,
                            "pressing_milliseconds": %d
                        }
                    })"),
                    button.getPressingAngle(),
                    button.getNotPressingAngle(),
                    button.getPressingMilliseconds()
                ).get()
            );
        }

        void clientErrorResponse(
            AsyncWebServerRequest &request,
            const String &error
        ) const {
            logger.warning(format(
                PSTR("ServoButtonController: %s"),
                error.c_str()
            ));

            request.send(
                HTTP_RESPONSE_STATUS_BAD_REQUEST,
                HTTP_RESPONSE_CONTENT_TYPE_JSON,
                format(
                    // language=JSON
                    PSTR(R"({"error": "%s"})"),
                    error.c_str()
                ).get()
            );
        }

        bool isValidAngle(const int angle) const {
            return angle >= Servo::MIN_ANGLE && angle <= Servo::MAX_ANGLE;
        }
    };

    static_assert(!std::is_abstract<ServoButtonController>());
}
