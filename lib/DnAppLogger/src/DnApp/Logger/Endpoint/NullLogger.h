#pragma once

#include <type_traits> // std::is_abstract

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Endpoint {
    class NullLogger final:
        public Logger {
    public:
        // required for our log() implementations not to hide existing base log() methods
        using Logger::log;

        auto log(const LOG_LEVEL level, const char* const message) -> void override {
            // do nothing
        };
    };

    static_assert(!std::is_abstract<NullLogger>());
}
