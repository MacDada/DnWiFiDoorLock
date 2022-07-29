#pragma once

#include <type_traits>

#include "Arduino/Servo/Servo.h"
#include "Arduino/SetupAndLoopAware.h"
#include "Logger/Logger.h"

namespace DnWiFiDoorLock {

    using Arduino::Servo::Servo;

    class DoorLock final: public Arduino::SetupAndLoopAware {
    public:
        explicit DoorLock(
            Servo &servo,
            Logger::Logger &logger,
            byte openAngle = Servo::MIN_ANGLE,
            byte closedAngle = Servo::MAX_ANGLE
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
        Servo &servo;

        Logger::Logger &logger;

        byte openAngle;

        byte closedAngle;
    };

    static_assert(!std::is_abstract<DoorLock>());

}
