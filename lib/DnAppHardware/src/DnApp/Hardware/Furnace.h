#pragma once

namespace DnApp::Hardware {
    class Furnace {
    public:
        [[nodiscard]]
        virtual
        auto isHeaterOn() const -> bool = 0;

        [[nodiscard]]
        virtual
        auto isHeaterOff() const -> bool = 0;

        virtual
        auto turnOnHeater() -> void = 0;

        virtual
        auto turnOffHeater() -> void = 0;

        virtual
        auto toggleHeater() -> void = 0;
    };
}
