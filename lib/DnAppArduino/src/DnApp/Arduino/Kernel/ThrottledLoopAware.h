#pragma once

#include <cstdint>     // uint32_t
#include <type_traits> // std::is_abstract

#include "DnApp/Arduino/Hardware/Board.h"
#include "DnApp/Arduino/Kernel/SetupAndLoopAware.h"

namespace DnApp::Arduino::Kernel {
    class ThrottledLoopAware final:
        public SetupAndLoopAware {
    public:
        explicit
        ThrottledLoopAware(
            SetupAndLoopAware& otherAware,
            const DnApp::Arduino::Hardware::Board& board,
            const int throttleMilliseconds
        ):
            otherAware{otherAware},
            board{board},
            throttleMilliseconds{throttleMilliseconds} {
        }

        auto onSetup() -> void override {
            otherAware.onSetup();
        }

        auto onLoop() -> void override {
            if (isItTime()) {
                otherAware.onLoop();

                lastOtherAwareCallMilliseconds = board.getUptime().getMilliseconds();
            }
        }
    private:
        SetupAndLoopAware& otherAware;

        const DnApp::Arduino::Hardware::Board& board;

        const int throttleMilliseconds;

        uint32_t lastOtherAwareCallMilliseconds = 0;

        auto isItTime() const -> bool  {
            return board.getUptime().getMilliseconds()
                // todo:[1] what to do with uint32_t overflow?
                //       I need to test what Arduino's `millis()` returns
                //       after its max value and think how I can handle
                //       such long uptimes
                //       -> prevent with scheduled restarts?
                //       -> restart on overflow?
                //       -> count how many times uptime was overflowed?
                > (lastOtherAwareCallMilliseconds + throttleMilliseconds);
        }
    };

    static_assert(!std::is_abstract<ThrottledLoopAware>());
}
