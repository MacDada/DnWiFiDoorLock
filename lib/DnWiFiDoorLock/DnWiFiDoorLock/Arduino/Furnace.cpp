#include "DnWiFiDoorLock/Arduino/Furnace.h"

namespace DnWiFiDoorLock::Arduino {

    Furnace::Furnace(
        Button &heaterButton,
        DnApp::Logger::Logger &logger
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
            logger.warning("Furnace: heater is already on");

            return;
        }

        logger.info("Furnace: turning on heater");
        heaterButton.press();
        heaterOn = true;
    }

    void Furnace::turnOffHeater() {
        if (!heaterOn) {
            logger.warning("Furnace: heater is already off");

            return;
        }

        logger.info("Furnace: turning off heater");
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
