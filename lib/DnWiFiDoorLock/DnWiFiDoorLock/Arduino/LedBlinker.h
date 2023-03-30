#pragma once

#include <Arduino.h>

#include "DnApp/Hardware/Led.h"
#include "DnWiFiDoorLock/Arduino/Board.h"

namespace DnWiFiDoorLock::Arduino {
    class LedBlinker final {
    public:
        explicit
        LedBlinker(
            DnWiFiDoorLock::Arduino::Board& board,
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
        DnWiFiDoorLock::Arduino::Board& board;

        DnApp::Hardware::Led& led;
    };
}
