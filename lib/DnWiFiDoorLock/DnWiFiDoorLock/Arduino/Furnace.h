#pragma once

#include <type_traits>

#include "DnWiFiDoorLock/Button.h"
#include "DnWiFiDoorLock/Furnace.h"
#include "DnApp/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino {

    class Furnace final:
        public DnWiFiDoorLock::Furnace {
    public:
        explicit Furnace(
            Button &heaterButton,
            DnApp::Logger::Logger &logger
        );

        bool isHeaterOn() const override;

        bool isHeaterOff() const override;

        void turnOnHeater() override;

        void turnOffHeater() override;

        void switchHeater() override;

    private:
        Button &heaterButton;

        DnApp::Logger::Logger &logger;

        bool heaterOn = false;
    };

    static_assert(!std::is_abstract<Furnace>());

}
