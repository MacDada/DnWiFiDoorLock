#pragma once

#include <type_traits> // std::is_abstract

#include <HardwareSerial.h>
#include <WString.h>

#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class HardwareSerialSetup final:
        public SetupAndLoopAware {
    public:
        explicit
        HardwareSerialSetup(
            HardwareSerial& serial,
            const DnWiFiDoorLock::Arduino::Hardware& hardware,
            const long bitsPerSecond
        ):
            serial{serial},
            hardware{hardware},
            bitsPerSecond{bitsPerSecond} {
        }

        void onSetup() override {
            serial.begin(bitsPerSecond);

            // waiting by uptime is not enough?!
            // without it the first Hello message is not printed :/
            hardware.pause(2000);

            // taken from https://github.com/khoih-prog/WiFiWebServer/blob/master/examples/HelloServer/HelloServer.ino#L90
            while (!Serial && hardware.getUptime().getSeconds() < 5) {
                // wait for serial port to open
            }

            serial.print(PSTR("\n\n\n\nHardwareSerial is working.\n"));
        }

        void onLoop() override {
            // do nothing
        }
    private:
        HardwareSerial& serial;

        const DnWiFiDoorLock::Arduino::Hardware& hardware;

        const long bitsPerSecond;
    };

    static_assert(!std::is_abstract<HardwareSerialSetup>());
}
