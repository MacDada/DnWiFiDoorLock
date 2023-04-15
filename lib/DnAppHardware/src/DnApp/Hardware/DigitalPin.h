#pragma once

namespace DnApp::Hardware {
    class DigitalPin {
    public:
        virtual
        auto setOutputMode() -> void = 0;

        virtual
        auto setInputMode() -> void = 0;

        virtual
        auto setHigh() -> void = 0;

        virtual
        auto setLow() -> void = 0;

        [[nodiscard]]
        virtual
        auto isHigh() const -> bool = 0;

        [[nodiscard]]
        virtual
        auto isLow() const -> bool = 0;
    };
}
