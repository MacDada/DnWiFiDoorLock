#pragma once

#include <vector>

#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {

    class MultipleSetupAndLoopAware final: public SetupAndLoopAware {
    public:
        explicit MultipleSetupAndLoopAware(
            const std::vector<SetupAndLoopAwareReference> &awares
        );

        void onSetup() override;

        void onLoop() override;

    private:
        const std::vector<SetupAndLoopAwareReference> &awares;
    };

    static_assert(!std::is_abstract<MultipleSetupAndLoopAware>());
}
