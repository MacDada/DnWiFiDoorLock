#pragma once

#include <type_traits> // std::is_abstract

#include "DnWiFiDoorLock/Arduino/Board.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class ThrottledLoopAware final:
        public SetupAndLoopAware {
    public:
        explicit
        ThrottledLoopAware(
            SetupAndLoopAware& otherAware,
            const DnWiFiDoorLock::Arduino::Board& board,
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

        const DnWiFiDoorLock::Arduino::Board& board;

        const int throttleMilliseconds;

        unsigned long lastOtherAwareCallMilliseconds = 0;

        auto isItTime() const -> bool  {
            return board.getUptime().getMilliseconds() > (lastOtherAwareCallMilliseconds + throttleMilliseconds);
        }
    };

    static_assert(!std::is_abstract<ThrottledLoopAware>());
}
