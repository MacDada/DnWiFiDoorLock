#pragma once

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

        unsigned long lastOtherAwareCallMilliseconds = 0;

        auto isItTime() const -> bool  {
            return board.getUptime().getMilliseconds() > (lastOtherAwareCallMilliseconds + throttleMilliseconds);
        }
    };

    static_assert(!std::is_abstract<ThrottledLoopAware>());
}