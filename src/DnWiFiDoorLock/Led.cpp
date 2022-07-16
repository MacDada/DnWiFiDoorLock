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
            delay(100);
            off();
            delay(100);
        }
    }

    void Led::blinkLong(const int count) {
        for (int i = 0; i < count; ++i) {
            on();
            delay(1000);
            off();
            delay(1000);
        }
    }

    void Led::blinkShortAndPause() {
        on();
        delay(50);
        off();
        delay(950);
    }

    void Led::blink1sPause1s() {
        on();
        delay(1000);
        off();
        delay(1000);
    }

}
