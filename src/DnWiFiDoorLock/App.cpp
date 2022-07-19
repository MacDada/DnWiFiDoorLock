#include "App.h"

namespace DnWiFiDoorLock {

    void App::informThatTheLoopHasStarted() {
        if (!hasLoopStarted) {
            logger.log("The Loop has started!");
            builtInLed.blinkFast(5);

            hasLoopStarted = true;
        }
    }

    void App::informTheLoopIsRunning() {
        informThatTheLoopHasStarted();

        builtInLed.blink1sPause1s();
        logger.log(Tools::format("The loop is running… [RSSI: %d dBm]", ::WiFi.RSSI()));
    }

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

        otaUpdater.setup();

        WebSerial.begin(&espServer);

        WebSerial.msgCallback([&](uint8_t *message, size_t messageLength) {
            onWebSerialIncoming(message, messageLength);
        });

        server.start();
    }

    void App::onLoop() {
        informTheLoopIsRunning();

        otaUpdater.handle();
        server.handleRequests();

        // todo: secure server
        // todo: handling door open/close with servo
    }

}