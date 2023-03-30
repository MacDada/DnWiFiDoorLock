#pragma once

#include <type_traits> // std::is_abstract

#include <HardwareSerial.h>
#include <WString.h>

#include "DnApp/Arduino/Hardware/Board.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class HardwareSerialSetup final:
        public SetupAndLoopAware {
    public:
        explicit
        HardwareSerialSetup(
            HardwareSerial& serial,
            DnApp::Arduino::Hardware::Board& board,
            const long bitsPerSecond
        ):
            serial{serial},
            board{board},
            bitsPerSecond{bitsPerSecond} {
        }

        auto onSetup() -> void override {
            serial.begin(bitsPerSecond);

            // waiting by uptime is not enough?!
            // without it the first Hello message is not printed :/
            board.pause(2000);

            // taken from https://github.com/khoih-prog/WiFiWebServer/blob/master/examples/HelloServer/HelloServer.ino#L90
            while (!Serial && board.getUptime().getSeconds() < 5) {
                // wait for serial port to open
            }

            serial.print(PSTR("\n\n\n\nHardwareSerial is working.\n"));
        }

        auto onLoop() -> void override {
            // do nothing
        }
    private:
        HardwareSerial& serial;

        DnApp::Arduino::Hardware::Board& board;

        const long bitsPerSecond;
    };

    static_assert(!std::is_abstract<HardwareSerialSetup>());
}
