#pragma once

namespace DnApp::Hardware {
    class DigitalPin {
    public:
        virtual
        void setOutputMode() = 0;

        virtual
        void setInputMode() = 0;

        virtual
        void setHigh() = 0;

        virtual
        void setLow() = 0;

        virtual
        bool isHigh() const = 0;

        virtual
        bool isLow() const = 0;
    };
}
