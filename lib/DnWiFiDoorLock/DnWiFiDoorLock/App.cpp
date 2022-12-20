#include "App.h"

namespace DnWiFiDoorLock {
    void App::onSetup() {
        getAppSetupAndLoopAwares().onSetup();
    }

    void App::onLoop() {
        getAppSetupAndLoopAwares().onLoop();

        // todo: secure server
        // todo: handling door open/close with servo
    }
}
