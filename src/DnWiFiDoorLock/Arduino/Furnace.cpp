#include "DnWiFiDoorLock/Arduino/Furnace.h"

namespace DnWiFiDoorLock::Arduino {

    Furnace::Furnace(
        Button &heaterButton,
        DnWiFiDoorLock::Logger::Logger &logger
    ):
        heaterButton(heaterButton),
        logger(logger) {
    }

    bool Furnace::isHeaterOn() const {
        return heaterOn;
    }

    bool Furnace::isHeaterOff() const {
        return !heaterOn;
    }

    void Furnace::turnOnHeater() {
        if (heaterOn) {
            logger.log("Furnace: heater is already on");

            return;
        }

        logger.log("Furnace: turning on heater");
        heaterButton.press();
        heaterOn = true;
    }

    void Furnace::turnOffHeater() {
        if (!heaterOn) {
            logger.log("Furnace: heater is already off");

            return;
        }

        logger.log("Furnace: turning off heater");
        heaterButton.press();
        heaterOn = false;
    }

    void Furnace::switchHeater() {
        if (isHeaterOn()) {
            turnOffHeater();
        } else {
            turnOnHeater();
        }
    }

}
