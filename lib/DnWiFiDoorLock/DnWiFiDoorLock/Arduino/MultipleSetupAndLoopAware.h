#pragma once

#include <vector>

#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class MultipleSetupAndLoopAware final:
        public SetupAndLoopAware {
    public:
        explicit
        MultipleSetupAndLoopAware(
            const std::vector<SetupAndLoopAwareReference>& awares
        ):
            awares{awares} {
        }

        void onSetup() override {
            for (auto& aware: awares) {
                aware.get().onSetup();
            }
        }

        void onLoop() override {
            for (auto& aware: awares) {
                aware.get().onLoop();
            }
        }
    private:
        const std::vector<SetupAndLoopAwareReference>& awares;
    };

    static_assert(!std::is_abstract<MultipleSetupAndLoopAware>());
}
