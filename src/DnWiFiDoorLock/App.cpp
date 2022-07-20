#include "App.h"

namespace DnWiFiDoorLock {

    void App::onSetup() {
        builtInLed.blinkFast(5);

        hardware.startSerial(SERIAL_BITS_PER_SECOND);

        hardwareSerialLogger.log("\n\n\n\n\n\n\n\n\n============\n\nHello from `DnWiFiDoorLock`!\n\n============");

        wiFi.connect();

        for (auto &setupAndLoopAware: setupAndLoopAwares) {
            setupAndLoopAware->onSetup();
        }
    }

    void App::onLoop() {
        for (auto &setupAndLoopAware: setupAndLoopAwares) {
            setupAndLoopAware->onLoop();
        }

        // todo: secure server
        // todo: handling door open/close with servo
    }

}
