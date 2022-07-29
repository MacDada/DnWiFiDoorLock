#pragma once

#include <type_traits>

#include <HardwareSerial.h>

#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {

    class HardwareSerialSetup: public SetupAndLoopAware {
    public:
        HardwareSerialSetup(
            HardwareSerial &serial,
            DnWiFiDoorLock::Arduino::Hardware &hardware,
            long bitsPerSecond
        );

        void onSetup() override;

        void onLoop() override;

    private:
        HardwareSerial &serial;

        DnWiFiDoorLock::Arduino::Hardware &hardware;

        const long bitsPerSecond;
    };

    static_assert(!std::is_abstract<HardwareSerialSetup>());

}
