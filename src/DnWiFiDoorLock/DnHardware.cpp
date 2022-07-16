#include "DnHardware.h"

namespace DnWiFiDoorLock {

    DnTime DnHardware::getUptime() {
        return DnTime(millis());
    }

    void DnHardware::setPinToOutputMode(const byte pin) {
        pinMode(pin, OUTPUT);
    }

    void DnHardware::digitalWriteLow(const byte pin) {
        digitalWrite(pin, LOW);
    }

    void DnHardware::digitalWriteHigh(const byte pin) {
        digitalWrite(pin, HIGH);
    }

    void DnHardware::startSerial(const long bitsPerSecond) {
        // to jest globalna zmienna dawana przez arduino
        // println po prostu nic nie robi jak nie będzie begin, ale nic się nie wywala
        Serial.begin(bitsPerSecond);

        // waiting by uptime is not enough?!
        // without it the first Hello message is not printed :/
        delay(2000);

        // wait for serial port to open
        // taken from https://github.com/khoih-prog/WiFiWebServer/blob/master/examples/HelloServer/HelloServer.ino#L90
        while (!Serial && getUptime().getSeconds() < 5);
    }

}
