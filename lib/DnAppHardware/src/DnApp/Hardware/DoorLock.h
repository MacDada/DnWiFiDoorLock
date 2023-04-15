#pragma once

namespace DnApp::Hardware {
    class DoorLock {
    public:
        [[nodiscard]]
        virtual
        auto isOpen() const -> bool = 0;

        [[nodiscard]]
        virtual
        auto isClosed() const -> bool = 0;

        virtual
        auto open() -> void = 0;

        virtual
        auto close() -> void = 0;

        virtual
        auto switchOpenClose() -> void = 0;
    };
}
