#include "Led.h"

namespace DnWiFiDoorLock::Arduino {

    Led::Led(
        const DnWiFiDoorLock::Arduino::Hardware &hardware,
        const byte pin
    ):
        hardware(hardware),
        pin(pin) {
        hardware.setPinToOutputMode(pin);
    }

    void Led::on() const {
        // todo: it is inverted for built–in led => so it should be high for normal led
        // https://github.com/nodemcu/nodemcu-devkit-v1.0/issues/16
        // https://stackoverflow.com/questions/46087828/why-is-nodemcu-triggering-gpio-in-reverse-when-using-lua
        hardware.digitalWriteLow(pin);
    }

    void Led::off() const {
        hardware.digitalWriteHigh(pin);
    }

    void Led::toggle() const {
        if (isOn()) {
            off();
        } else {
            on();
        }
    }

    bool Led::isOn() const {
        return hardware.isPinLow(pin);
    }

    bool Led::isOff() const {
        return hardware.isPinHigh(pin);
    }

    void Led::blinkFast(const int count) const {
        for (int i = 0; i < count; ++i) {
            on();
            hardware.pause(100);
            off();
            hardware.pause(100);
        }
    }

}
