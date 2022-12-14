#pragma once

#include <type_traits>

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Endpoint {
    class NullLogger final: public Logger {
    public:
        // required for our log() implementations not to hide existing base log() methods
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
