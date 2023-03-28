#pragma once

namespace DnApp::Hardware {
    class Button {
    public:
        virtual
        auto press() -> void = 0;
    };
}
