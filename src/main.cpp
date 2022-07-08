#include <Arduino.h>

#include "DnWiFiDoorLock/DnApp.h"

DnWiFiDoorLock::DnApp app;

void setup() {
    app.onSetup();
}

void loop() {
    app.onLoop();
}
