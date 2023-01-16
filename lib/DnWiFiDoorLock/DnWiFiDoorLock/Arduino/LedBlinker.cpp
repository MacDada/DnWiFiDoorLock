#include "LedBlinker.h"

namespace DnWiFiDoorLock::Arduino {
    LedBlinker::LedBlinker(
        const DnWiFiDoorLock::Arduino::Hardware& hardware,
        DnApp::Hardware::Led& led
    ):
        hardware{hardware},
        led{led} {
    }

    void LedBlinker::blinkFast(const int count) {
        for (int i = 0; i < count; ++i) {
            led.on();
            hardware.pause(100);
            led.off();
            hardware.pause(100);
        }
    }
}
