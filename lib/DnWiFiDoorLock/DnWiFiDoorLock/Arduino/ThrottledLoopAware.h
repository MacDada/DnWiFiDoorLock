#pragma once

#include <type_traits>

#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class ThrottledLoopAware final:
        public SetupAndLoopAware {
    public:
        explicit
        ThrottledLoopAware(
            SetupAndLoopAware& otherAware,
            const DnWiFiDoorLock::Arduino::Hardware& hardware,
            int throttleMilliseconds
        );

        void onSetup() override;

        void onLoop() override;
    private:
        SetupAndLoopAware& otherAware;

        const DnWiFiDoorLock::Arduino::Hardware& hardware;

        const int throttleMilliseconds;

        unsigned long lastOtherAwareCallMilliseconds = 0;

        bool isItTime() const;
    };

    static_assert(!std::is_abstract<ThrottledLoopAware>());
}
