#pragma once

namespace DnWiFiDoorLock {
    class DoorLock {
    public:
        virtual
        bool isOpen() const = 0;

        virtual
        bool isClosed() const = 0;

        virtual
        void open() = 0;

        virtual
        void close() = 0;

        virtual
        void switchOpenClose() = 0;
    };
}
