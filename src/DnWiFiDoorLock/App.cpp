#include "App.h"

namespace DnWiFiDoorLock {

    void App::onWebSerialIncoming(uint8_t *message, size_t messageLength) {
        String command = "";

        for (size_t i = 0; i < messageLength; i++) {
            command += char(message[i]);
        }

        WebSerial.println(Tools::format("Received command: \"%s\"", command.c_str()));

        if (command == "foo") {
            WebSerial.println("Foo command yo!");
        } else if (command == "bar") {
            WebSerial.println("Bar command yo!");
        }
    }

    void App::onSetup() {
        builtInLed.blinkFast(5);

        hardware.startSerial(SERIAL_BITS_PER_SECOND);

        hardwareSerialLogger.log("\n\n\n\n\n\n\n\n\n============\n\nHello from `DnWiFiDoorLock`!\n\n============");

        wiFi.connect();

        WebSerial.begin(&espServer);

        WebSerial.msgCallback([&](uint8_t *message, size_t messageLength) {
            onWebSerialIncoming(message, messageLength);
        });

        server.start();

        for (auto &setupAndLoopAware: setupAndLoopAwares) {
            setupAndLoopAware->onSetup();
        }
    }

    void App::onLoop() {
        for (auto &setupAndLoopAware: setupAndLoopAwares) {
            setupAndLoopAware->onLoop();
        }

        server.handleRequests();

        // todo: secure server
        // todo: handling door open/close with servo
    }

}
