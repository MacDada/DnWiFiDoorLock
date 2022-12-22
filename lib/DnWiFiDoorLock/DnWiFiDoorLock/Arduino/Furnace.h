#pragma once

#include <type_traits>

#include "DnApp/Hardware/Button.h"
#include "DnApp/Logger/Logger.h"
#include "DnWiFiDoorLock/Furnace.h"

namespace DnWiFiDoorLock::Arduino {
    class Furnace final:
        public DnWiFiDoorLock::Furnace {
    public:
        explicit
        Furnace(
            DnApp::Hardware::Button &heaterButton,
            DnApp::Logger::Logger &logger
        );

        bool isHeaterOn() const override;

        bool isHeaterOff() const override;

        void turnOnHeater() override;

        void turnOffHeater() override;

        void switchHeater() override;
    private:
        DnApp::Hardware::Button &heaterButton;

        DnApp::Logger::Logger &logger;

        bool heaterOn = false;
    };

    static_assert(!std::is_abstract<Furnace>());
}
