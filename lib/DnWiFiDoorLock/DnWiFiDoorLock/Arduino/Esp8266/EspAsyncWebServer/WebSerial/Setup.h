#pragma once

#include <type_traits> // std::is_abstract

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>
#include <WString.h>

#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial {
    class Setup:
        public SetupAndLoopAware {
    public:
        explicit
        Setup(
            WebSerialClass& serial,
            AsyncWebServer& server
        ):
            serial{serial},
            server{server} {
        }

        void onSetup() override {
            serial.begin(&server);

            serial.msgCallback([&] (uint8_t* const message, const size_t messageLength) {
                onWebSerialIncoming(message, messageLength);
            });
        }

        void onLoop() override {
            // do nothing
        }
    private:
        WebSerialClass& serial;

        AsyncWebServer& server;

        void onWebSerialIncoming(
            const uint8_t* const message,
            const size_t messageLength
        ) {
            String command = "";

            for (size_t i = 0; i < messageLength; i++) {
                command += char(message[i]);
            }

            serial.println(DnApp::Common::Strings::format(
                PSTR("Received command: \"%s\""),
                command.c_str()
            ).get());
        }
    };

    static_assert(!std::is_abstract<Setup>());
}
