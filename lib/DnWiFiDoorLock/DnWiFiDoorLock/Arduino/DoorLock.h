#pragma once

#include <type_traits> // std::is_abstract

#include <WString.h>

#include "DnApp/Hardware/DoorLock.h"
#include "DnApp/Logger/Decorator/PrefixPostfixMessageLoggerDecorator.h"
#include "DnApp/Logger/Logger.h"
#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class DoorLock final:
        public DnWiFiDoorLock::Arduino::SetupAndLoopAware,
        public DnApp::Hardware::DoorLock {
    private:
        using PrefixingLogger = DnApp
            ::Logger
            ::Decorator
            ::PrefixPostfixMessageLoggerDecorator;
    public:
        explicit
        DoorLock(
            Servo::Servo& servo,
            DnApp::Logger::Logger& logger,
            const byte openAngle,
            const byte closedAngle
        ):
            servo{servo},
            logger{PrefixingLogger{logger, PSTR("DoorLock: ")}},
            openAngle{openAngle},
            closedAngle{closedAngle} {
        }

        // warning! it only shows what we asked the servo to do
        //          we have no feedback as for the servo succeeded to open the door or not
        //
        // todo: "Clang-Tidy: Function 'isOpen' should be marked [[nodiscard]]"?
        auto isOpen() const -> bool override {
            // we're not checking for openAngle,
            // because if we have any other angle than the closedAngle
            // then it's better to assume the door is open
            return !isClosed();
        }

        // warning! it only shows what we asked the servo to do
        //          we have no feedback as for the servo succeeded to close the door or not
        auto isClosed() const -> bool override {
            return servo.getAngle() == closedAngle;
        }

        auto open() -> void override {
            logger.info(PSTR("Opening"));

            servo.setAngle(openAngle);
        }

        auto close() -> void override {
            logger.info(PSTR("Closing"));

            servo.setAngle(closedAngle);
        }

        auto switchOpenClose() -> void override {
            if (isOpen()) {
                close();
            } else {
                open();
            }
        }

        auto onSetup() -> void override {
            // the door should be closed by default for security reasons
            // (for example unexpected device restart)
            //
            // we're doing it in the setup, not in the constructor,
            // because the dependencies need their setup as well
            close();
        }

        auto onLoop() -> void override {
            // do nothing
        }
    private:
        Servo::Servo& servo;

        PrefixingLogger logger;

        const byte openAngle;

        const byte closedAngle;
    };

    static_assert(!std::is_abstract<DoorLock>());
}
