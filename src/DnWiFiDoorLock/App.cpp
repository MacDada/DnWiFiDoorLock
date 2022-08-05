#include "App.h"

namespace DnWiFiDoorLock {

    void App::onSetup() {
        getBuiltInLed().blinkFast(5);

        for (auto &setupAndLoopAware: getSetupAndLoopAwares()) {
            setupAndLoopAware.get().onSetup();
        }
    }

    void App::onLoop() {
        for (auto &setupAndLoopAware: getSetupAndLoopAwares()) {
            setupAndLoopAware.get().onLoop();
        }

        // todo: secure server
        // todo: handling door open/close with servo
    }

}
