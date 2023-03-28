#pragma once

#include <string>

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Endpoint {
    class StringLogger final:
        public DnApp::Logger::Logger {
    public:
        auto getContent() const -> const char* {
            return string.c_str();
        }

        auto clear() -> void {
            string = "";
        }

        // Required, because otherwise our `log()` methods
        // would hide base class declarations.
        using DnApp::Logger::Logger::log;

        auto log(const LOG_LEVEL level, const char* const message) -> void override {
            string += Logger::logLevelToString(level);
            string += "\n";
            string += message;
            string += "\n";
        }
    private:
        std::string string;
    };
}
