#pragma once

#include <WString.h>

#include "DnApp/Logger/Logger.h"

namespace DnApp::Arduino::Logger {
    /**
     * Added sugar methods to handle Arduino's `String`.
     */
    class WithArduinoStringLogger:
        public DnApp::Logger::Logger {
    public:
        // we need this NOT to hide base implementations
        using DnApp::Logger::Logger::log;
        using DnApp::Logger::Logger::debug;
        using DnApp::Logger::Logger::info;
        using DnApp::Logger::Logger::warning;
        using DnApp::Logger::Logger::error;
        using DnApp::Logger::Logger::critical;

        auto log(const LOG_LEVEL level, const String& message) -> void {
            log(level, message.c_str());
        }

        auto debug(const String& message) -> void {
            log(LOG_LEVEL::DEBUG, message.c_str());
        }

        auto info(const String& message) -> void {
            log(LOG_LEVEL::INFO, message.c_str());
        }

        auto warning(const String& message) -> void {
            log(LOG_LEVEL::WARNING, message.c_str());
        }

        auto error(const String& message) -> void {
            log(LOG_LEVEL::ERROR, message.c_str());
        }

        auto critical(const String& message) -> void {
            log(LOG_LEVEL::CRITICAL, message.c_str());
        }
    };
}
