#pragma once

#include <type_traits>

#include <WString.h>

#include "DnApp/Hardware/Button.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Hardware/Furnace.h"

namespace DnWiFiDoorLock::Arduino {
    class Furnace final:
        public DnApp::Hardware::Furnace {
    public:
        explicit
        Furnace(
            DnApp::Hardware::Button& heaterButton,
            DnApp::Logger::Logger& logger
        ):
            heaterButton{heaterButton},
            logger{logger} {
        }

        bool isHeaterOn() const override {
            return heaterOn;
        }

        bool isHeaterOff() const override {
            return !heaterOn;
        }

        void turnOnHeater() override {
            if (heaterOn) {
                logger.warning(PSTR("Furnace: the heater is already on"));

                return;
            }

            logger.info(PSTR("Furnace: turning on the heater"));
            heaterButton.press();
            heaterOn = true;
        }

        void turnOffHeater() override {
            if (!heaterOn) {
                logger.warning(PSTR("Furnace: the heater is already off"));

                return;
            }

            logger.info(PSTR("Furnace: turning off the heater"));
            heaterButton.press();
            heaterOn = false;
        }

        void toggleHeater() override {
            if (isHeaterOn()) {
                turnOffHeater();
            } else {
                turnOnHeater();
            }
        }
    private:
        DnApp::Hardware::Button& heaterButton;

        DnApp::Logger::Logger& logger;

        bool heaterOn = false;
    };

    static_assert(!std::is_abstract<Furnace>());
}
