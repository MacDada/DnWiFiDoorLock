#pragma once

#include <span>

#include "DnApp/Arduino/Kernel/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class MultipleSetupAndLoopAware final:
        public DnApp::Arduino::Kernel::SetupAndLoopAware {
    public:
        explicit
        MultipleSetupAndLoopAware(
            const std::span<
                const DnApp::Arduino::Kernel::SetupAndLoopAwareReference
            > awares
        ):
            awares{awares} {
        }

        auto onSetup() -> void override {
            for (const auto& aware: awares) {
                aware.get().onSetup();
            }
        }

        auto onLoop() -> void override {
            for (const auto& aware: awares) {
                aware.get().onLoop();
            }
        }
    private:
        const std::span<
            const DnApp::Arduino::Kernel::SetupAndLoopAwareReference
        > awares;
    };

    static_assert(!std::is_abstract<MultipleSetupAndLoopAware>());
}
