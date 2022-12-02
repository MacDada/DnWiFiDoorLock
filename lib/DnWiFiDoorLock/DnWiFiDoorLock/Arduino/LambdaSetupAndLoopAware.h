#pragma once

#include <functional>
#include <utility>

#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {

    class LambdaSetupAndLoopAware final: public SetupAndLoopAware {
    public:
        static LambdaSetupAndLoopAware createSetupAware(
            std::function<void()> onSetupCallback
        );

        static LambdaSetupAndLoopAware createLoopAware(
            std::function<void()> onLoopCallback
        );

        explicit LambdaSetupAndLoopAware(
            std::function<void()> onSetupCallback,
            std::function<void()> onLoopCallback
        );

        void onSetup() override;

        void onLoop() override;

    private:
        const std::function<void()> onSetupCallback;

        const std::function<void()> onLoopCallback;
    };

    static_assert(!std::is_abstract<LambdaSetupAndLoopAware>());

}
