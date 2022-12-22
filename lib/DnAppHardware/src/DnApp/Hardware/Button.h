#pragma once

namespace DnApp::Hardware {
    class Button {
    public:
        virtual
        void press() = 0;
    };
}
