#pragma once

#include <type_traits>

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger {
    class NullLogger final: public Logger {
    public:
        // required because otherwise our log() methods hide base class declarations
        using Logger::log;

        void log(LOG_LEVEL level, char *message) override {
            // do nothing
        };

        void log(LOG_LEVEL level, const char *message) override {
            // do nothing
        };
    };

    static_assert(!std::is_abstract<NullLogger>());
}
