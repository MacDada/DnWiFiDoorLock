#pragma once

#include <type_traits>

#include <HardwareSerial.h>
#include <WString.h>

#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class HardwareSerialSetup: public SetupAndLoopAware {
    public:
        explicit
        HardwareSerialSetup(
            HardwareSerial& serial,
            const DnWiFiDoorLock::Arduino::Hardware& hardware,
            const long bitsPerSecond,
            const char* const appName
        ):
            serial{serial},
            hardware{hardware},
            bitsPerSecond{bitsPerSecond},
            appName{appName} {
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

            // todo: do not hardcode app name
            serial.print(DnApp::Common::Strings::format(
                PSTR(
                    "\n\n\n\n\n\n\n\n\n"
                    "%s"
                    "================================"
                    "%s"
                    "\n\n"
                    "%s"
                    "  Hello from `%s`!"
                    "%s"
                    "\n\n"
                    "%s"
                    "================================"
                    "%s"
                    "\n\n\n"
                ),
                VT100_FORMAT_BOLD_BLUE,
                VT100_FORMAT_RESET,
                VT100_FORMAT_BOLD_GREEN,
                appName,
                VT100_FORMAT_RESET,
                VT100_FORMAT_BOLD_BLUE,
                VT100_FORMAT_RESET
            ).get());
        }

        void onLoop() override {
            // do nothing
        }
    private:
        static
        PROGMEM
        constexpr
        const char* const VT100_FORMAT_RESET = "\e[0m";

        static
        PROGMEM
        constexpr
        const char* const VT100_FORMAT_BOLD_BLUE = "\e[1;34m";

        static
        PROGMEM
        constexpr
        const char* const VT100_FORMAT_BOLD_GREEN = "\e[1;32m";

        HardwareSerial& serial;

        const DnWiFiDoorLock::Arduino::Hardware& hardware;

        const long bitsPerSecond;

        const char* const appName;
    };

    static_assert(!std::is_abstract<HardwareSerialSetup>());
}
