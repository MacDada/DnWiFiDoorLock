#include "Setup.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial {
    Setup::Setup(
        WebSerialClass& serial,
        AsyncWebServer& server
    ):
        serial{serial},
        server{server} {
    }

    void Setup::onSetup() {
        serial.begin(&server);

        serial.msgCallback([&](uint8_t* const message, const size_t messageLength) {
            onWebSerialIncoming(message, messageLength);
        });
    }

    void Setup::onLoop() {
        // do nothing
    }

    void Setup::onWebSerialIncoming(
        uint8_t* const message,
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
}
