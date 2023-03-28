#pragma once

namespace DnApp::Hardware {
    class Led {
    public:
        virtual
        auto isOn() const -> bool = 0;

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
