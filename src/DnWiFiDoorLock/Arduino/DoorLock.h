#pragma once

#include <type_traits>

#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino {

    class DoorLock final: public DnWiFiDoorLock::Arduino::SetupAndLoopAware {
    public:
        explicit DoorLock(
            Servo::Servo &servo,
            Logger::Logger &logger,
            byte openAngle = Servo::Servo::MIN_ANGLE,
            byte closedAngle = Servo::Servo::MAX_ANGLE
        );

        // todo: "Clang-Tidy: Function 'isOpen' should be marked [[nodiscard]]"?
        bool isOpen() const;

        bool isClosed() const;

        void open();

        void close();

        void switchOpenClose();

        void onSetup() override;

        void onLoop() override;

    private:
        Servo::Servo &servo;

        Logger::Logger &logger;

        byte openAngle;

        byte closedAngle;
    };

    static_assert(!std::is_abstract<DoorLock>());

}
