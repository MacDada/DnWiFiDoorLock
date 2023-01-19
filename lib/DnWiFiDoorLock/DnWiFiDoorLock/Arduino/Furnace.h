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
        );

        bool isHeaterOn() const override;

        bool isHeaterOff() const override;

        void turnOnHeater() override;

        void turnOffHeater() override;

        void toggleHeater() override;
    private:
        DnApp::Hardware::Button& heaterButton;

        DnApp::Logger::Logger& logger;

        bool heaterOn = false;
    };

    static_assert(!std::is_abstract<Furnace>());
}
