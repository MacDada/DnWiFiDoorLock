#include "DnApp.h"

using namespace DnWiFiDoorLock;

void DnApp::informThatTheLoopHasStarted() {
    if (!hasLoopStarted) {
        logger.log("The Loop has started!");
        WebSerial.println("The Loop has started!");
        builtInLed.blinkFast(5);

        hasLoopStarted = true;
    }
}

void DnApp::informTheLoopIsRunning() {
    informThatTheLoopHasStarted();

    builtInLed.blink1sPause1s();
    logger.log("The loop is running…");
    WebSerial.println("The Loop has started!");
}

void DnApp::onWebSerialIncoming(uint8_t *message, size_t messageLength) {
    WebSerial.println("Received Data…");

    String command = "";

    for (int i = 0; i < messageLength; i++) {
        command += char(message[i]);
    }

    WebSerial.println(command);

    if (command == "foo") {
        WebSerial.println("Foo command yo!");
    } else if (command == "bar") {
        WebSerial.println("Bar command yo!");
    }
}

void DnApp::onSetup() {
    builtInLed.blinkFast(5);

    hardware.startSerial(SERIAL_BITS_PER_SECOND);

    logger.log("\n\n\n\n\n\n\n\n\n============\n\nHello from `DnWiFiDoorLock`!\n\n============");

    wiFi.connect();

    otaUpdater.setup();

    WebSerial.begin(&espServer);

    WebSerial.msgCallback([&](uint8_t *message, size_t messageLength) {
        onWebSerialIncoming(message, messageLength);
    });

    server.start();
}

void DnApp::onLoop() {
    informTheLoopIsRunning();

    otaUpdater.handle();
    server.handleRequests();

    // todo: secure server
    // todo: handling door open/close with servo
}
