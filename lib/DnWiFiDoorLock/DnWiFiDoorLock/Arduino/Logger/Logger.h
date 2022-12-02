#pragma once

#include <functional>

#include <Arduino.h>

#include "DnApp/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class Logger: public DnApp::Logger::Logger {
    public:
        // we need this NOT to hide base implementations
        using DnApp::Logger::Logger::log;
        using DnApp::Logger::Logger::debug;
        using DnApp::Logger::Logger::info;
        using DnApp::Logger::Logger::warning;
        using DnApp::Logger::Logger::error;
        using DnApp::Logger::Logger::critical;

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
