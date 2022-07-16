#include "DoorLock.h"

namespace DnWiFiDoorLock {

    bool DoorLock::isOpen() const {
        return !closed;
    }

    bool DoorLock::isClosed() const {
        return closed;
    }

    void DoorLock::open() {
        closed = false;
    }

    void DoorLock::close() {
        closed = true;
    }

    void DoorLock::switchOpenClose() {
        closed = !closed;
    }

}
