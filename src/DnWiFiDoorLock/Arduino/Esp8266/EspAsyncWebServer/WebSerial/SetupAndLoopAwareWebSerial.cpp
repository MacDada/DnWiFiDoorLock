#include "SetupAndLoopAwareWebSerial.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial {

    SetupAndLoopAwareWebSerial::SetupAndLoopAwareWebSerial(
        WebSerialClass &serial,
        AsyncWebServer &server
    ):
        serial(serial),
        server(server) {
    }

    void SetupAndLoopAwareWebSerial::onSetup() {
        serial.begin(&server);

        serial.msgCallback([&](uint8_t *message, size_t messageLength) {
            onWebSerialIncoming(message, messageLength);
        });
    }

    void SetupAndLoopAwareWebSerial::onLoop() {
        // do nothing
    }

    void SetupAndLoopAwareWebSerial::onWebSerialIncoming(uint8_t *message, size_t messageLength) {
        String command = "";

        for (size_t i = 0; i < messageLength; i++) {
            command += char(message[i]);
        }

        serial.println(Tools::format("Received command: \"%s\"", command.c_str()).get());
    }

}
