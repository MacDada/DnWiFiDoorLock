#include "DnWiFiDoorLock/App.h"

DnWiFiDoorLock::App app{};

void setup() {
    app.onSetup();
}

void loop() {
    app.onLoop();
}
