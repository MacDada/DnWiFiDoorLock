#pragma once

#include <WebSerial.h>

#include "DnApp/Logger/Endpoint/PrinterLogger.h"

namespace DnApp::Esp::Logger::Endpoint {
    using WebSerialLogger = DnApp::Logger::Endpoint::PrinterLogger<WebSerialClass>;
}
