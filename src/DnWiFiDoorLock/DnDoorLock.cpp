#include "DnDoorLock.h"

namespace DnWiFiDoorLock {

    bool DnDoorLock::isOpen() const {
        return !closed;
    }

    bool DnDoorLock::isClosed() const {
        return closed;
    }

    void DnDoorLock::open() {
        closed = false;
    }

    void DnDoorLock::close() {
        closed = true;
    }

    void DnDoorLock::switchOpenClose() {
        closed = !closed;
    }

}
