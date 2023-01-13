#pragma once

#include <string>

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Endpoint {
    class StringLogger final:
        public DnApp::Logger::Logger {
    public:
        using DnApp::Logger::Logger::log;

        const char* getContent() const {
            return string.c_str();
        }

        void clear() {
            string = "";
        }

        void log(LOG_LEVEL level, char* message) override {
            doLog(level, message);
        }

        void log(LOG_LEVEL level, const char* message) override {
            doLog(level, message);
        }
    private:
        std::string string;

        template<typename MessageType>
        void doLog(LOG_LEVEL level, const MessageType message) {
            string += LOG_LEVELS[static_cast<int>(level)];
            string += "\n";
            string += message;
            string += "\n";
        }
    };
}
