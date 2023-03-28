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

        auto onSetup() -> void override {
            serial.begin(&server);

            serial.msgCallback([&] (uint8_t* const message, const size_t messageLength) {
                onWebSerialIncoming(message, messageLength);
            });
        }

        auto onLoop() -> void override {
            // do nothing
        }
    private:
        WebSerialClass& serial;

        AsyncWebServer& server;

        auto onWebSerialIncoming(
            const uint8_t* const message,
            const size_t messageLength
        ) -> void {
            auto command = String{""};

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
