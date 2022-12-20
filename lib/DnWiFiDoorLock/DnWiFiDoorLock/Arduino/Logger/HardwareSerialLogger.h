#pragma once

#include <Arduino.h>

#include "DnWiFiDoorLock/Arduino/Logger/PrintLnLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {
    using HardwareSerialLogger = PrintLnLogger<HardwareSerial>;

    static_assert(!std::is_abstract<HardwareSerialLogger>());
}
