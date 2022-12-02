#pragma once

#include <functional>

#include <Arduino.h>

#include "DnWiFiDoorLock/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class Logger: public DnWiFiDoorLock::Logger::Logger {
    public:
        // we need this NOT to hide base implementations
        using DnWiFiDoorLock::Logger::Logger::log;
        using DnWiFiDoorLock::Logger::Logger::debug;
        using DnWiFiDoorLock::Logger::Logger::info;
        using DnWiFiDoorLock::Logger::Logger::warning;
        using DnWiFiDoorLock::Logger::Logger::error;
        using DnWiFiDoorLock::Logger::Logger::critical;

        void log(LOG_LEVEL level, const String &message) {
            log(level, message.c_str());
        }

        void debug(const String &message) {
            log(LOG_LEVEL::DEBUG, message.c_str());
        }

        void info(const String &message) {
            log(LOG_LEVEL::INFO, message.c_str());
        }

        void warning(const String &message) {
            log(LOG_LEVEL::WARNING, message.c_str());
        }

        void error(const String &message) {
            log(LOG_LEVEL::ERROR, message.c_str());
        }

        void critical(const String &message) {
            log(LOG_LEVEL::CRITICAL, message.c_str());
        }
    };

    using LoggerReference = std::reference_wrapper<Logger>;

}
