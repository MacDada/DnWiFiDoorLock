#include "Hardware.h"

namespace DnWiFiDoorLock {

    void Hardware::pause(const unsigned long milliseconds) {
        delay(milliseconds);
    }

    Time Hardware::getUptime() {
        return Time(millis());
    }

    void Hardware::setPinToOutputMode(const byte pin) {
        pinMode(pin, OUTPUT);
    }

    void Hardware::digitalWriteLow(const byte pin) {
        digitalWrite(pin, LOW);
    }

    void Hardware::digitalWriteHigh(const byte pin) {
        digitalWrite(pin, HIGH);
    }

}
