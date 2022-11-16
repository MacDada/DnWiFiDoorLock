#pragma once

#include <functional>

#include <Arduino.h>

#include "DnWiFiDoorLock/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class Logger: public DnWiFiDoorLock::Logger::Logger {
    public:
        virtual void log(LOG_LEVEL level, const String &message) = 0;

        virtual void log(LOG_LEVEL level, std::unique_ptr<char[]> message) override = 0;

        virtual void log(LOG_LEVEL level, const char *message) override = 0;

        virtual void log(LOG_LEVEL level, char *message) override = 0;
    };

    using LoggerReference = std::reference_wrapper<Logger>;

}
