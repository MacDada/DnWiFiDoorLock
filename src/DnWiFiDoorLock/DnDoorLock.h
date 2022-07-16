#pragma once

namespace DnWiFiDoorLock {

    class DnDoorLock final {
    public:
        bool isOpen() const;

        bool isClosed() const;

        void open();

        void close();

        void switchOpenClose();

    private:
        // it is better to assume it is open
        // and force closing if needed
        bool closed = false;
    };

}
