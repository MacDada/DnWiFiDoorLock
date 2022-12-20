#pragma once

#include <type_traits>

#include <HardwareSerial.h>

#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class HardwareSerialSetup: public SetupAndLoopAware {
    public:
        HardwareSerialSetup(
            HardwareSerial &serial,
            const DnWiFiDoorLock::Arduino::Hardware &hardware,
            long bitsPerSecond
        );

        void onSetup() override;

        void onLoop() override;
    private:
        static constexpr const char *const VT100_FORMAT_RESET = "\e[0m";

        static constexpr const char *const VT100_FORMAT_BOLD_BLUE = "\e[1;34m";

        static constexpr const char *const VT100_FORMAT_BOLD_GREEN = "\e[1;32m";

        HardwareSerial &serial;

        const DnWiFiDoorLock::Arduino::Hardware &hardware;

        const long bitsPerSecond;
    };

    static_assert(!std::is_abstract<HardwareSerialSetup>());
}
