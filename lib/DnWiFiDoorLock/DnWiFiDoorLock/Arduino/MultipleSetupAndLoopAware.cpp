#include "MultipleSetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    MultipleSetupAndLoopAware::MultipleSetupAndLoopAware(
        const std::vector<SetupAndLoopAwareReference>& awares
    ):
        awares{awares} {
    }

    void MultipleSetupAndLoopAware::onSetup() {
        for (auto& aware: awares) {
            aware.get().onSetup();
        }
    }

    void MultipleSetupAndLoopAware::onLoop() {
        for (auto& aware: awares) {
            aware.get().onLoop();
        }
    }
}
