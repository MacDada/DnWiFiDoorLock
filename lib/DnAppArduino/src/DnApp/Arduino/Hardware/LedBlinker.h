#pragma once

#include "DnApp/Arduino/Hardware/Board.h"
#include "DnApp/Hardware/Led.h"

namespace DnApp::Arduino::Hardware {
    class LedBlinker final {
    public:
        explicit
        LedBlinker(
            Board& board,
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
        Board& board;

        DnApp::Hardware::Led& led;
    };
}
