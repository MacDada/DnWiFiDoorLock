#pragma once

#include <type_traits>

#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {

    class ThrottledLoopAware final: public SetupAndLoopAware {
    public:
        ThrottledLoopAware(
            SetupAndLoopAware &otherAware,
            DnWiFiDoorLock::Arduino::Hardware &hardware,
            int throttleMilliseconds
        );

        void onSetup() override;

        void onLoop() override;

    private:
        SetupAndLoopAware &otherAware;

        DnWiFiDoorLock::Arduino::Hardware &hardware;

        int throttleMilliseconds;

        unsigned long lastOtherAwareCallMilliseconds = 0;

        bool isItTime();
    };

    static_assert(!std::is_abstract<ThrottledLoopAware>());

}
