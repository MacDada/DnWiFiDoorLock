#pragma once

namespace DnWiFiDoorLock::Arduino {

    class SetupAndLoopAware {
    public:
        virtual void onSetup() = 0;

        virtual void onLoop() = 0;
    };

}
