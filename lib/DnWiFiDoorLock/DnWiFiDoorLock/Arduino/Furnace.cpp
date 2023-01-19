#include "DnWiFiDoorLock/Arduino/Furnace.h"

namespace DnWiFiDoorLock::Arduino {
    Furnace::Furnace(
        DnApp::Hardware::Button& heaterButton,
        DnApp::Logger::Logger& logger
    ):
        heaterButton{heaterButton},
        logger{logger} {
    }

    bool Furnace::isHeaterOn() const {
        return heaterOn;
    }

    bool Furnace::isHeaterOff() const {
        return !heaterOn;
    }

    void Furnace::turnOnHeater() {
        if (heaterOn) {
            logger.warning(PSTR("Furnace: the heater is already on"));

            return;
        }

        logger.info(PSTR("Furnace: turning on the heater"));
        heaterButton.press();
        heaterOn = true;
    }

    void Furnace::turnOffHeater() {
        if (!heaterOn) {
            logger.warning(PSTR("Furnace: the heater is already off"));

            return;
        }

        logger.info(PSTR("Furnace: turning off the heater"));
        heaterButton.press();
        heaterOn = false;
    }

    void Furnace::toggleHeater() {
        if (isHeaterOn()) {
            turnOffHeater();
        } else {
            turnOnHeater();
        }
    }
}
