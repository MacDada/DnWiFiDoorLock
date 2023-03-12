#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"

namespace DnApp::Arduino::Logger::Endpoint {
    class WithArduinoStringNullLogger final:
        public WithArduinoStringLogger {
    public:
        // Required, because otherwise our `log()` methods
        // would hide base class declarations.
        using WithArduinoStringLogger::log;

        void log(const LOG_LEVEL level, const char* const message) override {
            // do nothing
        };
    };

    static_assert(!std::is_abstract<WithArduinoStringNullLogger>());
}
