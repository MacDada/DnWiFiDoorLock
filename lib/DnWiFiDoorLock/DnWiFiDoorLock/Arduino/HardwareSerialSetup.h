#pragma once

#include <type_traits>

#include <HardwareSerial.h>
#include <WString.h>

#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class HardwareSerialSetup: public SetupAndLoopAware {
    public:
        explicit
        HardwareSerialSetup(
            HardwareSerial &serial,
            const DnWiFiDoorLock::Arduino::Hardware &hardware,
            const long bitsPerSecond,
            const char *const appName
        );

        void onSetup() override;

        void onLoop() override;
    private:
        static
        PROGMEM
        constexpr
        const char *const VT100_FORMAT_RESET = "\e[0m";

        static
        PROGMEM
        constexpr
        const char *const VT100_FORMAT_BOLD_BLUE = "\e[1;34m";

        static
        PROGMEM
        constexpr
        const char *const VT100_FORMAT_BOLD_GREEN = "\e[1;32m";

        HardwareSerial &serial;

        const DnWiFiDoorLock::Arduino::Hardware &hardware;

        const long bitsPerSecond;

        const char *const appName;
    };

    static_assert(!std::is_abstract<HardwareSerialSetup>());
}
