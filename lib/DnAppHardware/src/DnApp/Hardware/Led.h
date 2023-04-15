#pragma once

namespace DnApp::Hardware {
    class Led {
    public:
        [[nodiscard]]
        virtual
        auto isOn() const -> bool = 0;

        [[nodiscard]]
        virtual
        auto isOff() const -> bool = 0;

        virtual
        auto on() -> void = 0;

        virtual
        auto off() -> void = 0;

        virtual
        auto toggle() -> void = 0;
    };
}
