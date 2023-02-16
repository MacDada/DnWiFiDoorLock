#pragma once

#include <string>

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Endpoint {
    class StringLogger final:
        public DnApp::Logger::Logger {
    public:
        const char* getContent() const {
            return string.c_str();
        }

        void clear() {
            string = "";
        }

        // Required, because otherwise our `log()` methods
        // would hide base class declarations.
        using DnApp::Logger::Logger::log;

        void log(LOG_LEVEL level, const char* message) override {
            string += Logger::logLevelToString(level);
            string += "\n";
            string += message;
            string += "\n";
        }
    private:
        std::string string;
    };
}
