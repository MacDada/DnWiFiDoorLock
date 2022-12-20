#include "Hardware.h"

namespace DnWiFiDoorLock::Arduino {
    void Hardware::pause(const unsigned long milliseconds) const {
        delay(milliseconds);
    }

    Time Hardware::getUptime() const {
        return Time(millis());
    }

    void Hardware::setPinToInputMode(const byte pin) const {
        pinMode(pin, INPUT);
    }

    void Hardware::setPinToOutputMode(const byte pin) const {
        pinMode(pin, OUTPUT);
    }

    void Hardware::digitalWriteLow(const byte pin) const {
        digitalWrite(pin, LOW);
    }

    void Hardware::digitalWriteHigh(const byte pin) const {
        digitalWrite(pin, HIGH);
    }

    bool Hardware::isPinHigh(const byte pin) const {
        return digitalRead(pin) == HIGH;
    }

    bool Hardware::isPinLow(const byte pin) const {
        return digitalRead(pin) == LOW;
    }
}
