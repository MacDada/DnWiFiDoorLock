#include "Led.h"

namespace DnWiFiDoorLock {

    Led::Led(
        Hardware &hardware,
        const byte pin
    ):
        hardware(hardware),
        pin(pin) {
        hardware.setPinToOutputMode(pin);
    }

    void Led::on() {
        hardware.digitalWriteLow(pin);
    }

    void Led::off() {
        hardware.digitalWriteHigh(pin);
    }

    void Led::toggle() {
        if (isOn()) {
            off();
        } else {
            on();
        }
    }

    bool Led::isOn() {
        return hardware.isPinLow(pin);
    }

    bool Led::isOff() {
        return hardware.isPinHigh(pin);
    }

    void Led::blinkFast(const int count) {
        for (int i = 0; i < count; ++i) {
            on();
            hardware.pause(100);
            off();
            hardware.pause(100);
        }
    }

}
