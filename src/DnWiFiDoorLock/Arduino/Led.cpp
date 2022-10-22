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
        // it is inverted for built–in led => so it should be high for normal led
        // https://github.com/nodemcu/nodemcu-devkit-v1.0/issues/16
        // https://stackoverflow.com/questions/46087828/why-is-nodemcu-triggering-gpio-in-reverse-when-using-lua
        if (LED_BUILTIN == pin) {
            hardware.digitalWriteLow(pin);
        } else {
            hardware.digitalWriteHigh(pin);
        }
    }

    void Led::off() const {
        if (LED_BUILTIN == pin) {
            hardware.digitalWriteHigh(pin);
        } else {
            hardware.digitalWriteLow(pin);
        }
    }

    void Led::toggle() const {
        if (isOn()) {
            off();
        } else {
            on();
        }
    }

    bool Led::isOn() const {
        if (LED_BUILTIN == pin) {
            return hardware.isPinLow(pin);
        } else {
            return hardware.isPinHigh(pin);
        }
    }

    bool Led::isOff() const {
        if (LED_BUILTIN == pin) {
            return hardware.isPinHigh(pin);
        } else {
            return hardware.isPinLow(pin);
        }
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
