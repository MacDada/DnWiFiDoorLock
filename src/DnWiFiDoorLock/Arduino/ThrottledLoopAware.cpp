#include "ThrottledLoopAware.h"

namespace DnWiFiDoorLock::Arduino {

    ThrottledLoopAware::ThrottledLoopAware(
        SetupAndLoopAware &otherAware,
        DnWiFiDoorLock::Arduino::Hardware &hardware,
        const int throttleMilliseconds
    ):
        otherAware(otherAware),
        hardware(hardware),
        throttleMilliseconds(throttleMilliseconds) {
    }

    void ThrottledLoopAware::onSetup() {
        otherAware.onSetup();
    }

    void ThrottledLoopAware::onLoop() {
        if (isItTime()) {
            otherAware.onLoop();

            lastOtherAwareCallMilliseconds = hardware.getUptime().getMilliseconds();
        }
    }

    bool ThrottledLoopAware::isItTime() const {
        return hardware.getUptime().getMilliseconds() > (lastOtherAwareCallMilliseconds + throttleMilliseconds);
    }

}
