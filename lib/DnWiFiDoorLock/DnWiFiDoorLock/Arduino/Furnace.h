#pragma once

#include <type_traits> // std::is_abstract

#include <WString.h>

#include "DnApp/Hardware/Button.h"
#include "DnApp/Logger/Decorator/PrefixPostfixMessageLoggerDecorator.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Hardware/Furnace.h"

namespace DnWiFiDoorLock::Arduino {
    class Furnace final:
        public DnApp::Hardware::Furnace {
    private:
        using PrefixingLogger = DnApp
            ::Logger
            ::Decorator
            ::PrefixPostfixMessageLoggerDecorator;
    public:
        explicit
        Furnace(
            DnApp::Hardware::Button& heaterButton,
            DnApp::Logger::Logger& logger
        ):
            heaterButton{heaterButton},
            logger{PrefixingLogger{logger, PSTR("Furnace: ")}} {
        }

        bool isHeaterOn() const override {
            return heaterOn;
        }

        bool isHeaterOff() const override {
            return !heaterOn;
        }

        void turnOnHeater() override {
            if (heaterOn) {
                logger.warning(PSTR("The heater is already on"));

                return;
            }

            logger.info(PSTR("Turning on the heater"));
            heaterButton.press();
            heaterOn = true;
        }

        void turnOffHeater() override {
            if (!heaterOn) {
                logger.warning(PSTR("The heater is already off"));

                return;
            }

            logger.info(PSTR("Turning off the heater"));
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

        PrefixingLogger logger;

        bool heaterOn = false;
    };

    static_assert(!std::is_abstract<Furnace>());
}
