#pragma once

#include <functional> // std::function
#include <utility>    // std::move

#include "DnApp/Arduino/Kernel/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class LambdaSetupAndLoopAware final:
        public DnApp::Arduino::Kernel::SetupAndLoopAware {
    public:
        static
        auto createSetupAware(
            std::function<void()> onSetupCallback
        ) -> LambdaSetupAndLoopAware {
            return LambdaSetupAndLoopAware(
                std::move(onSetupCallback),
                [] () {}
            );
        }

        static
        auto createLoopAware(
            std::function<void()> onLoopCallback
        ) -> LambdaSetupAndLoopAware {
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

        auto onSetup() -> void override {
            onSetupCallback();
        }

        auto onLoop() -> void override {
            onLoopCallback();
        }
    private:
        const std::function<void()> onSetupCallback;

        const std::function<void()> onLoopCallback;
    };

    static_assert(!std::is_abstract<LambdaSetupAndLoopAware>());
}
