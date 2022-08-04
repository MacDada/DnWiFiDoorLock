#pragma once

#include <functional>

namespace DnWiFiDoorLock::Arduino {

    class SetupAndLoopAware {
    public:
        virtual void onSetup() = 0;

        virtual void onLoop() = 0;
    };

    using SetupAndLoopAwareReference = std::reference_wrapper<SetupAndLoopAware>;

}
