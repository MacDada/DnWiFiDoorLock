#pragma once

#include <functional>

#include <Arduino.h>

#include "DnWiFiDoorLock/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class Logger: public DnWiFiDoorLock::Logger::Logger {
    public:
        using DnWiFiDoorLock::Logger::Logger::log;

        void log(LOG_LEVEL level, const String &message) {
            log(level, message.c_str());
        }
    };

    using LoggerReference = std::reference_wrapper<Logger>;

}
