#include "App.h"

namespace DnWiFiDoorLock {

    void App::onSetup() {
        getBuiltInLed().blinkFast(5);

        getAppSetupAndLoopAwares().onSetup();
    }

    void App::onLoop() {
        getAppSetupAndLoopAwares().onLoop();

        // todo: secure server
        // todo: handling door open/close with servo
    }

}
