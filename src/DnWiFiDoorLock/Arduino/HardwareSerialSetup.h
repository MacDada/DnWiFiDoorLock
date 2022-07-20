#pragma once

#include <type_traits>
#include <HardwareSerial.h>

#include "SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Hardware.h"

namespace DnWiFiDoorLock::Arduino {

    class HardwareSerialSetup: public SetupAndLoopAware {
    public:
        HardwareSerialSetup(
            HardwareSerial &serial,
            Hardware &hardware,
            long bitsPerSecond
        );

        void onSetup() override;

        void onLoop() override;

    private:
        HardwareSerial &serial;

        Hardware &hardware;

        const long bitsPerSecond;
    };

    static_assert(!std::is_abstract<HardwareSerialSetup>());

}
