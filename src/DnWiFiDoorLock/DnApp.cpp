#include "DnApp.h"

using namespace DnWiFiDoorLock;

void DnApp::informThatTheLoopHasStarted() {
    if (!hasLoopStarted) {
        Serial.println("The Loop has started!");
        builtInLed.blinkFast(5);

        hasLoopStarted = true;
    }
}

void DnApp::informTheLoopIsRunning() {
    informThatTheLoopHasStarted();

    builtInLed.blink1sPause1s();
    Serial.println("The loop is running…");
}

void DnApp::onSetup() {
    builtInLed.blinkFast(5);

    hardware.startSerial(SERIAL_BITS_PER_SECOND);

    Serial.println("\n\n\n\n\n\n\n\n\n============\n\nHello from `doorlockservo-esp8266`!\n\n============");

    wiFi.connect();
    server.start();
}

void DnApp::onLoop() {
    informTheLoopIsRunning();
    server.handleRequests();

    // todo: secure server
    // todo: handling door open/close with servo
}
