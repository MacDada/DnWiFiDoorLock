#include "LambdaSetupAndLoopAware.h"

#include <utility>

namespace DnWiFiDoorLock::Arduino {
    LambdaSetupAndLoopAware LambdaSetupAndLoopAware::createSetupAware(
        std::function<void()> onSetupCallback
    ) {
        return LambdaSetupAndLoopAware(
            std::move(onSetupCallback),
            []() {}
        );
    }

    LambdaSetupAndLoopAware LambdaSetupAndLoopAware::createLoopAware(
        std::function<void()> onLoopCallback
    ) {
        return LambdaSetupAndLoopAware(
            []() {},
            std::move(onLoopCallback)
        );
    }

    LambdaSetupAndLoopAware::LambdaSetupAndLoopAware(
        std::function<void()> onSetupCallback,
        std::function<void()> onLoopCallback
    ):
        onSetupCallback{std::move(onSetupCallback)},
        onLoopCallback{std::move(onLoopCallback)} {
    }

    void LambdaSetupAndLoopAware::onSetup() {
        onSetupCallback();
    }

    void LambdaSetupAndLoopAware::onLoop() {
        onLoopCallback();
    }
}
