#pragma once

#include <functional>
#include <type_traits>
#include <utility>

#include <ESPAsyncWebServer.h>
#include <WString.h>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
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

        void onSetup() override {
            setupRouting();

            server.begin();

            logServerHasStarted();
        }

        void onLoop() override {
            // do nothing
        }
    private:
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

        void handleWebNotFound(AsyncWebServerRequest &request) {
            logger.warning(DnApp::Common::Strings::format(
                PSTR("HttpServer: page not found! URI: %s, method: %s"),
                request.url().c_str(),
                request.methodToString()
            ));

            request.send(
                404,
                PSTR("text/plain"),
                DnApp::Common::Strings::format(
                    PSTR("File Not Found\n\nURI: %s\nMethod: %s\n"),
                    request.url().c_str(),
                    request.methodToString()
                ).get()
            );
        }

        void setupRouting() {
            registerRoute(PSTR("/"), HTTP_GET, [&](AsyncWebServerRequest& request) {
                request.redirect(PSTR("/furnace"));
            });

            registerRoute(PSTR("/doorlock"), HTTP_GET, [&](AsyncWebServerRequest& request) {
                doorLockController.statusAction(request);
            });

            registerRoute(PSTR("/doorlock/switch"), HTTP_POST, [&](AsyncWebServerRequest& request) {
                doorLockController.switchAction(request);
            });

            registerRoute(PSTR("/furnace"), HTTP_GET, [&](AsyncWebServerRequest& request) {
                furnaceController.statusAction(request);
            });

            registerRoute(PSTR("/furnace/switch"), HTTP_POST, [&](AsyncWebServerRequest& request) {
                furnaceController.switchAction(request);
            });

            registerRoute(PSTR("/api/furnace"), HTTP_GET, [&](AsyncWebServerRequest& request) {
                furnaceController.apiGetAction(request);
            });

            registerRoute(PSTR("/api/furnace"), HTTP_POST, [&](AsyncWebServerRequest& request, const String& body) {
                furnaceController.apiPostAction(request, body);
            });

            registerRoute(PSTR("/modal.css"), HTTP_GET, [&](AsyncWebServerRequest& request) {
                servoButtonController.modalCssAction(request);
            });

            registerRoute(PSTR("/modal.js"), HTTP_GET, [&](AsyncWebServerRequest& request) {
                servoButtonController.modalJsAction(request);
            });

            registerRoute(PSTR("/ajax-form.js"), HTTP_GET, [&](AsyncWebServerRequest& request) {
                servoButtonController.ajaxFormJsAction(request);
            });

            registerRoute(PSTR("/input-number-buttons.js"), HTTP_GET, [&](AsyncWebServerRequest& request) {
                servoButtonController.inputNumberButtonsJsAction(request);
            });

            registerRoute(PSTR("/servo-button.js"), HTTP_GET, [&](AsyncWebServerRequest& request) {
                servoButtonController.javascriptAction(request);
            });

            registerRoute(PSTR("/servo-button.css"), HTTP_GET, [&](AsyncWebServerRequest& request) {
                servoButtonController.cssAction(request);
            });

            registerRoute(PSTR("/servo-button"), HTTP_POST, [&](AsyncWebServerRequest& request) {
                servoButtonController.updateSettingsAction(request);
            });

            registerRoute(PSTR("/servo-button"), HTTP_GET, [&](AsyncWebServerRequest& request) {
                servoButtonController.showSettingsAction(request);
            });

            registerRoute(PSTR("/servo"), HTTP_GET | HTTP_POST, [&](AsyncWebServerRequest& request) {
                servoController.angleAction(request);
            });

            server.onNotFound([&](AsyncWebServerRequest* const request) {
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

        void registerRoute(
            const char* const uri,
            const WebRequestMethodComposite method,
            OnRequestCallback onRequest
        ) {
            server.on(uri, method, [&, onRequest = std::move(onRequest)](
                AsyncWebServerRequest* const request
            ) {
                // https://discord.com/channels/583251190591258624/742849025191051326/995832013405835316
                //
                // todo: in theory, i can have a nullptr instead of the request object -> need to handle that
                onRequest(*request);
            });
        }

        void registerRoute(
            const char* const uri,
            const WebRequestMethodComposite method,
            OnRequestBodyCallback onRequestBody
        ) {
            server.on(uri, method, [&](AsyncWebServerRequest* const request) {
                // ignore, we use the callback with request body
            }, nullptr, [&, onRequestBody = std::move(onRequestBody)](
                AsyncWebServerRequest* request,
                uint8_t* bodyData,
                size_t bodyDataLength,
                size_t index,
                size_t total
            ) {
                const String message = dataToString(bodyData, bodyDataLength);

                onRequestBody(*request, message);
            });
        }

        void logServerHasStarted() {
            String message{PSTR("HTTP server has started, open http://")};

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

        String dataToString(
            const uint8_t* const data,
            const size_t dataLength
        ) const {
            String string;
            string.reserve(dataLength);

            for (size_t i = 0; i < dataLength; i++) {
                string += char(data[i]);
            }

            return string;
        }
    };

    static_assert(!std::is_abstract<ServerSetup>());
}
