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

    void Led::blinkFast(const int count) {
        for (int i = 0; i < count; ++i) {
            on();
            hardware.pause(100);
            off();
            hardware.pause(100);
        }
    }

    void Led::blinkLong(const int count) {
        for (int i = 0; i < count; ++i) {
            on();
            hardware.pause(1000);
            off();
            hardware.pause(1000);
        }
    }

    void Led::blinkShortAndPause() {
        on();
        hardware.pause(50);
        off();
        hardware.pause(950);
    }

    void Led::blink1sPause1s() {
        on();
        hardware.pause(1000);
        off();
        hardware.pause(1000);
    }

}
