#pragma once

#include <Arduino.h>
#include <WebSerial.h>

#include "DnWiFiDoorLock/Arduino/Logger/PrintLnLogger.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial {
    using Logger = DnWiFiDoorLock::Arduino::Logger::PrintLnLogger<WebSerialClass>;

    static_assert(!std::is_abstract<Logger>());
}
