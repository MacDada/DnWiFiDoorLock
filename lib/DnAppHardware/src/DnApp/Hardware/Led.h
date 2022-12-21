#pragma once

namespace DnApp::Hardware {
    class Led {
    public:
        virtual
        bool isOn() const = 0;

        virtual
        bool isOff() const = 0;

        virtual
        void on() = 0;

        virtual
        void off() = 0;

        virtual
        void toggle() = 0;
    };
}
