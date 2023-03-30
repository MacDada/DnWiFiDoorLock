#pragma once

#include <functional>  // std::function
#include <type_traits> // std::is_abstract
#include <utility>     // std::move

#include <ESPAsyncWebServer.h>
#include <WString.h>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Arduino/functions.h"
#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/DoorLockController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/FurnaceController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/ServoButtonController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/ServoController.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http {
    class ServerSetup final:
        public DnWiFiDoorLock::Arduino::SetupAndLoopAware {
    private:
        using Logger = DnApp::Arduino::Logger::WithArduinoStringLogger;
    public:
        explicit
        ServerSetup(
            ESP8266WiFiClass& wiFi,
            AsyncWebServer& server,
            const char* const hostname,
            const unsigned int port,
            DoorLockController& doorLockController,
            FurnaceController& furnaceController,
            ServoButtonController& servoButtonController,
            ServoController& servoController,
            Logger& logger
        ):
            wiFi{wiFi},
            server{server},
            hostname{hostname},
            port{port},
            doorLockController{doorLockController},
            furnaceController{furnaceController},
            servoButtonController{servoButtonController},
            servoController{servoController},
            logger{logger} {
        }

        auto onSetup() -> void override {
            setupRouting();

            server.begin();

            logServerHasStarted();
        }

        auto onLoop() -> void override {
            // do nothing
        }
    private:
        static
        constexpr
        const
        auto format = DnApp::Common::Strings::format;

        ESP8266WiFiClass& wiFi;

        AsyncWebServer& server;

        const char* const hostname;

        const unsigned int port;

        // todo: controllers should register themselves to avoid having 2137 controllers here?
        DoorLockController& doorLockController;

        FurnaceController& furnaceController;

        ServoButtonController& servoButtonController;

        ServoController& servoController;

        Logger& logger;

        auto handleWebNotFound(AsyncWebServerRequest &request) const -> void {
            logger.warning(format(
                PSTR("HttpServer: page not found! URI: %s, method: %s"),
                request.url().c_str(),
                request.methodToString()
            ));

            request.send(
                404,
                PSTR("text/plain"),
                format(
                    PSTR("File Not Found\n\nURI: %s\nMethod: %s\n"),
                    request.url().c_str(),
                    request.methodToString()
                ).get()
            );
        }

        auto setupRouting() -> void {
            registerRoute(
                PSTR("app.index"),
                PSTR("/"),
                HTTP_GET,
                [] (AsyncWebServerRequest& request) {
                    request.redirect(PSTR("/furnace"));
                }
            );

            registerRoute(
                PSTR("app.doorlock.index"),
                PSTR("/doorlock"),
                HTTP_GET,
                [&] (AsyncWebServerRequest& request) {
                    doorLockController.statusAction(request);
                }
            );

            registerRoute(
                PSTR("app.doorlock.switch"),
                PSTR("/doorlock/switch"),
                HTTP_POST,
                [&] (AsyncWebServerRequest& request) {
                    doorLockController.switchAction(request);
                }
            );

            registerRoute(
                PSTR("app.furnace.index"),
                PSTR("/furnace"), HTTP_GET,
                [&] (AsyncWebServerRequest& request) {
                    furnaceController.statusAction(request);
                }
            );

            registerRoute(
                PSTR("app.furnace.switch"),
                PSTR("/furnace/switch"),
                HTTP_POST,
                [&] (AsyncWebServerRequest& request) {
                    furnaceController.switchAction(request);
                }
            );

            registerRoute(
                PSTR("app.furnace.api.get"),
                PSTR("/api/furnace"),
                HTTP_GET,
                [&] (AsyncWebServerRequest& request) {
                    furnaceController.apiGetAction(request);
                }
            );

            registerRoute(
                PSTR("app.furnace.api.post"),
                PSTR("/api/furnace"),
                HTTP_POST,
                [&] (AsyncWebServerRequest& request, const String& body) {
                    furnaceController.apiPostAction(request, body);
                }
            );

            registerRoute(
                PSTR("app.assets.modal.css"),
                PSTR("/modal.css"),
                HTTP_GET,
                [&] (AsyncWebServerRequest& request) {
                    servoButtonController.modalCssAction(request);
                }
            );

            registerRoute(
                PSTR("app.assets.modal.js"),
                PSTR("/modal.js"),
                HTTP_GET,
                [&] (AsyncWebServerRequest& request) {
                    servoButtonController.modalJsAction(request);
                }
            );

            registerRoute(
                PSTR("app.assets.ajax_form.js"),
                PSTR("/ajax-form.js"),
                HTTP_GET,
                [&] (AsyncWebServerRequest& request) {
                    servoButtonController.ajaxFormJsAction(request);
                }
            );

            registerRoute(
                PSTR("app.assets.input_number_buttons.js"),
                PSTR("/input-number-buttons.js"),
                HTTP_GET,
                [&] (AsyncWebServerRequest& request) {
                    servoButtonController.inputNumberButtonsJsAction(request);
                }
            );

            registerRoute(
                PSTR("app.assets.servo_button.js"),
                PSTR("/servo-button.js"),
                HTTP_GET,
                [&] (AsyncWebServerRequest& request) {
                    servoButtonController.javascriptAction(request);
                }
            );

            registerRoute(
                PSTR("app.assets.servo_button.css"),
                PSTR("/servo-button.css"),
                HTTP_GET,
                [&] (AsyncWebServerRequest& request) {
                    servoButtonController.cssAction(request);
                }
            );

            registerRoute(
                PSTR("app.servo_button.update"),
                PSTR("/servo-button"),
                HTTP_POST,
                [&] (AsyncWebServerRequest& request) {
                    servoButtonController.updateSettingsAction(request);
                }
            );

            registerRoute(
                PSTR("app.servo_button.show"),
                PSTR("/servo-button"),
                HTTP_GET,
                [&] (AsyncWebServerRequest& request) {
                    servoButtonController.showSettingsAction(request);
                }
            );

            registerRoute(
                PSTR("app.servo.angle"),
                PSTR("/servo"),
                HTTP_GET | HTTP_POST,
                [&] (AsyncWebServerRequest& request) {
                    servoController.angleAction(request);
                }
            );

            server.onNotFound([&] (AsyncWebServerRequest* const request) {
                assertRequestWasGiven(request);

                handleWebNotFound(*request);
            });
        }

        using OnRequestCallback = std::function<void(
            AsyncWebServerRequest& request
        )>;

        using OnRequestBodyCallback = std::function<void(
            AsyncWebServerRequest& request,
            const String& body
        )>;

        auto registerRoute(
            const char* const name,
            const char* const uri,
            const WebRequestMethodComposite method,
            OnRequestCallback onRequest
        ) -> void {
            server.on(uri, method, [&, name, onRequest = std::move(onRequest)] (
                AsyncWebServerRequest* const request
            ) {
                onMatchedRoute(name, request);

                onRequest(*request);
            });
        }

        auto registerRoute(
            const char* const name,
            const char* const uri,
            const WebRequestMethodComposite method,
            OnRequestBodyCallback onRequestBody
        ) -> void {
            server.on(uri, method, [] (const AsyncWebServerRequest* const) {
                // cannot be nullptr or the route is not found o.O
                // ignore it: we use the callback with request body
            }, nullptr, [&, name, onRequestBody = std::move(onRequestBody)] (
                AsyncWebServerRequest* const request,
                const uint8_t* bodyData,
                const size_t bodyDataLength,
                const size_t index,
                const size_t total
            ) {
                onMatchedRoute(name, request);

                onRequestBody(
                    *request,
                    DnApp::Arduino::functions::dataToString(
                        bodyData,
                        bodyDataLength
                    )
                );
            });
        }

        auto onMatchedRoute(
            const char* const routeName,
            AsyncWebServerRequest* const request
        ) -> void {
            assertRequestWasGiven(request);

            const auto requestMethod = request->methodToString();
            const auto requestUrl = request->url().c_str();

            logger.debug(format(
                PSTR("HttpServer: matched route: %s: %s %s"),
                routeName,
                requestMethod,
                requestUrl
            ));

            request->onDisconnect([&, routeName, requestMethod, requestUrl] {
                logger.debug(format(
                    PSTR("HttpServer: disconnected client: %s: %s %s"),
                    routeName,
                    requestMethod,
                    requestUrl
                ));
            });
        }

        auto assertRequestWasGiven(const AsyncWebServerRequest* const request) -> void {
            if (nullptr == request) {
                logger.critical(PSTR(
                    "HttpServer: `AsyncWebServerRequest` object expected, `nullptr` given!"
                ));

                // We cannot recover -> no Request given, no way to respond (even with 500).
                //
                // todo: Maybe I should avoid panicking (and thus restarting the device),
                //       -> just log and skip the response?
                // todo: Maybe a universal "problem indicator"?
                //          * Special LED flashing
                //          * Try to log to a configurable external service?
                // todo: Can I attach my own callback to the general panic handler?
                panic();
            }
        }

        auto logServerHasStarted() const -> void {
            auto message = String{PSTR("HTTP server has started, open http://")};

            message += wiFi.localIP().toString();

            message += PSTR(":");
            message += port;
            message += PSTR(" or http://");
            message += hostname;
            message += PSTR(".local:");
            message += port;
            message += PSTR(" in a web browser :)");

            logger.info(message);
        }
    };

    static_assert(!std::is_abstract<ServerSetup>());
}
