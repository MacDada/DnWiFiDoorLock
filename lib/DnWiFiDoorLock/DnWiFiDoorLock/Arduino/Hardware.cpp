#include "Hardware.h"

namespace DnWiFiDoorLock::Arduino {
    void Hardware::pause(const unsigned long milliseconds) const {
        delay(milliseconds);
    }

    Time Hardware::getUptime() const {
        return Time(millis());
    }
}
