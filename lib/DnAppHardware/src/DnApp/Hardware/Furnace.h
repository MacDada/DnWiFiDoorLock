#pragma once

namespace DnApp::Hardware {
    class Furnace {
    public:
        virtual
        bool isHeaterOn() const = 0;

        virtual
        bool isHeaterOff() const = 0;

        virtual
        void turnOnHeater() = 0;

        virtual
        void turnOffHeater() = 0;

        virtual
        void toggleHeater() = 0;
    };
}
