#pragma once

#include <functional> // std::function
#include <utility>    // std::move

#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class LambdaSetupAndLoopAware final:
        public SetupAndLoopAware {
    public:
        static
        LambdaSetupAndLoopAware createSetupAware(
            std::function<void()> onSetupCallback
        ) {
            return LambdaSetupAndLoopAware(
                std::move(onSetupCallback),
                [] () {}
            );
        }

        static
        LambdaSetupAndLoopAware createLoopAware(
            std::function<void()> onLoopCallback
        ) {
            return LambdaSetupAndLoopAware(
                [] () {},
                std::move(onLoopCallback)
            );
        }

        explicit
        LambdaSetupAndLoopAware(
            std::function<void()> onSetupCallback,
            std::function<void()> onLoopCallback
        ):
            onSetupCallback{std::move(onSetupCallback)},
            onLoopCallback{std::move(onLoopCallback)} {
        }

        void onSetup() override {
            onSetupCallback();
        }

        void onLoop() override {
            onLoopCallback();
        }
    private:
        const std::function<void()> onSetupCallback;

        const std::function<void()> onLoopCallback;
    };

    static_assert(!std::is_abstract<LambdaSetupAndLoopAware>());
}
