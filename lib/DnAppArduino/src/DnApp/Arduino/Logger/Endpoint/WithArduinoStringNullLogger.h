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

        auto log(const LOG_LEVEL level, const char* const message) -> void override {
            // fix `[-Wunused-parameter]` warnings:
            static_cast<void>(level);
            static_cast<void>(message);

            // do nothing
        };
    };

    static_assert(!std::is_abstract<WithArduinoStringNullLogger>());
}
