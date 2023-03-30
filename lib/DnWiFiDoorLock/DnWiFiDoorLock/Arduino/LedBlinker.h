#pragma once

#include <Arduino.h>

#include "DnApp/Arduino/Hardware/Board.h"
#include "DnApp/Hardware/Led.h"

namespace DnWiFiDoorLock::Arduino {
    class LedBlinker final {
    public:
        explicit
        LedBlinker(
            DnApp::Arduino::Hardware::Board& board,
            DnApp::Hardware::Led& led
        ):
            board{board},
            led{led} {
        }

        auto blinkFast(const int count) -> void {
            for (auto i = decltype(count){0}; i < count; ++i) {
                led.on();
                board.pause(100);
                led.off();
                board.pause(100);
            }
        }
    private:
        DnApp::Arduino::Hardware::Board& board;

        DnApp::Hardware::Led& led;
    };
}
