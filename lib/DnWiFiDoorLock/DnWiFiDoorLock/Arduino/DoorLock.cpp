#include "DnWiFiDoorLock/Arduino/DoorLock.h"

namespace DnWiFiDoorLock::Arduino {
    DoorLock::DoorLock(
        Servo::Servo &servo,
        DnApp::Logger::Logger &logger,
        const byte openAngle,
        const byte closedAngle
    ):
        servo(servo),
        logger(logger),
        openAngle(openAngle),
        closedAngle(closedAngle) {
    }

    void DoorLock::onSetup() {
        // the door should be closed by default for security reasons
        // (for example unexpected device restart)
        //
        // we're doing it in the setup, not in the constructor,
        // because the dependencies need their setup as well
        close();
    }

    void DoorLock::onLoop() {
        // do nothing
    }

    // warning! it only shows what we asked the servo to do
    //          we have no feedback as for the servo succeeded to open the door or not
    bool DoorLock::isOpen() const {
        // we're not checking for openAngle,
        // because if we have any other angle than the closedAngle
        // then it's better to assume the door is open
        return !isClosed();
    }

    // warning! it only shows what we asked the servo to do
    //          we have no feedback as for the servo succeeded to close the door or not
    bool DoorLock::isClosed() const {
        return servo.getAngle() == closedAngle;
    }

    void DoorLock::open() {
        logger.info(PSTR("DoorLock: opening"));

        servo.setAngle(openAngle);
    }

    void DoorLock::close() {
        logger.info(PSTR("DoorLock: closing"));

        servo.setAngle(closedAngle);
    }

    void DoorLock::switchOpenClose() {
        if (isOpen()) {
            close();
        } else {
            open();
        }
    }
}
