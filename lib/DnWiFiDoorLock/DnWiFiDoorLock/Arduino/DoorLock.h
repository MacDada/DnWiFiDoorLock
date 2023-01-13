#pragma once

#include <type_traits>

#include <WString.h>

#include "DnApp/Hardware/DoorLock.h"
#include "DnApp/Logger/Logger.h"
#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class DoorLock final:
        public DnWiFiDoorLock::Arduino::SetupAndLoopAware,
        public DnApp::Hardware::DoorLock {
    public:
        explicit
        DoorLock(
            Servo::Servo& servo,
            DnApp::Logger::Logger& logger,
            byte openAngle = Servo::Servo::MIN_ANGLE,
            byte closedAngle = Servo::Servo::MAX_ANGLE
        );

        // todo: "Clang-Tidy: Function 'isOpen' should be marked [[nodiscard]]"?
        bool isOpen() const override;

        bool isClosed() const override;

        void open() override;

        void close() override;

        void switchOpenClose() override;

        void onSetup() override;

        void onLoop() override;
    private:
        Servo::Servo& servo;

        DnApp::Logger::Logger& logger;

        const byte openAngle;

        const byte closedAngle;
    };

    static_assert(!std::is_abstract<DoorLock>());
}
