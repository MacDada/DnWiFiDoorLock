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
            const int throttleMilliseconds
        ):
            otherAware{otherAware},
            hardware{hardware},
            throttleMilliseconds{throttleMilliseconds} {
        }

        void onSetup() override {
            otherAware.onSetup();
        }

        void onLoop() override {
            if (isItTime()) {
                otherAware.onLoop();

                lastOtherAwareCallMilliseconds = hardware.getUptime().getMilliseconds();
            }
        }
    private:
        SetupAndLoopAware& otherAware;

        const DnWiFiDoorLock::Arduino::Hardware& hardware;

        const int throttleMilliseconds;

        unsigned long lastOtherAwareCallMilliseconds = 0;

        bool isItTime() const {
            return hardware.getUptime().getMilliseconds() > (lastOtherAwareCallMilliseconds + throttleMilliseconds);
        }
    };

    static_assert(!std::is_abstract<ThrottledLoopAware>());
}
