#include "App.h"

namespace DnWiFiDoorLock {

    void App::onSetup() {
        builtInLed.blinkFast(5);

        for (auto &setupAndLoopAware: setupAndLoopAwares) {
            setupAndLoopAware.get().onSetup();
        }
    }

    void App::onLoop() {
        for (auto &setupAndLoopAware: setupAndLoopAwares) {
            setupAndLoopAware.get().onLoop();
        }

        // todo: secure server
        // todo: handling door open/close with servo
    }

}
