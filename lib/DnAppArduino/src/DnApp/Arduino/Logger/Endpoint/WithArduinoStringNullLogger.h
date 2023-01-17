#pragma once

#include <type_traits>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"

namespace DnApp::Arduino::Logger::Endpoint {
    class WithArduinoStringNullLogger final:
        public WithArduinoStringLogger {
    public:
        // Required, because otherwise our `log()` methods
        // would hide base class declarations.
        using WithArduinoStringLogger::log;

        void log(LOG_LEVEL level, char *message) override {
            // do nothing
        };

        void log(LOG_LEVEL level, const char *message) override {
            // do nothing
        };
    };

    static_assert(!std::is_abstract<WithArduinoStringNullLogger>());
}
