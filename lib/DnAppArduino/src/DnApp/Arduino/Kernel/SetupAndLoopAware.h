#pragma once

#include <functional> // std::reference_wrapper

namespace DnApp::Arduino::Kernel {
    class SetupAndLoopAware {
    public:
        virtual auto onSetup() -> void = 0;

        virtual auto onLoop() -> void = 0;
    };

    using SetupAndLoopAwareReference = std::reference_wrapper<SetupAndLoopAware>;
}
