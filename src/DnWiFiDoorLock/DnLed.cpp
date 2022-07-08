#include "DnLed.h"

using namespace DnWiFiDoorLock;

DnLed::DnLed(DnHardware &hardware, const byte pin) {
    this->hardware = &hardware;
    this->pin = pin;

    this->hardware->setPinToOutputMode(pin);
}

void DnLed::on() {
    hardware->digitalWriteLow(pin);
}

void DnLed::off() {
    hardware->digitalWriteHigh(pin);
}

void DnLed::blinkFast(const int count) {
    for (int i = 0; i < count; ++i) {
        on();
        delay(100);
        off();
        delay(100);
    }
}

void DnLed::blinkLong(const int count) {
    for (int i = 0; i < count; ++i) {
        on();
        delay(1000);
        off();
        delay(1000);
    }
}

void DnLed::blinkShortAndPause() {
    on();
    delay(50);
    off();
    delay(950);
}

void DnLed::blink1sPause1s() {
    on();
    delay(1000);
    off();
    delay(1000);
}
