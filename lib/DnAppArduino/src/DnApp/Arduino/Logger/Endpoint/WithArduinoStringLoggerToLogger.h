#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Logger/Logger.h"

namespace DnApp::Arduino::Logger::Endpoint {
    class WithArduinoStringLoggerToLogger final:
        public WithArduinoStringLogger {
    public:
        explicit
        WithArduinoStringLoggerToLogger(
            DnApp::Logger::Logger& logger
        ) noexcept:
            logger{logger} {
        }

        // Required, because otherwise our `log()` methods
        // would hide base class declarations.
        using WithArduinoStringLogger::log;

        void log(const LOG_LEVEL level, const char* const message) override {
            logger.log(level, message);
        };
    private:
        DnApp::Logger::Logger& logger;
    };

    static_assert(!std::is_abstract<WithArduinoStringLoggerToLogger>());
}
