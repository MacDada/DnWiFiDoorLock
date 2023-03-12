#pragma once

#include <type_traits> // std::is_abstract

#include <Arduino.h>

#include "DnApp/Logger/Endpoint/PrinterLogger.h"

namespace DnApp::Arduino::Logger::Endpoint {
    using HardwareSerialLogger = DnApp::Logger::Endpoint::PrinterLogger<HardwareSerial>;

    static_assert(!std::is_abstract<HardwareSerialLogger>());
}
