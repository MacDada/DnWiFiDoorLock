#pragma once

#include <type_traits>

#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Decorator {
    class PrependLogLevelLogger final:
        public Logger {
    public:
        // required because otherwise our log() methods hide base class declarations
        using Logger::log;

        explicit
        PrependLogLevelLogger(Logger& logger) noexcept:
            logger(logger) {
        }

        void log(LOG_LEVEL level, const char* message) override {
            doLog(level, message);
        };

        void log(LOG_LEVEL level, char* message) override {
            doLog(level, message);
        };
    private:
        Logger& logger;

        template<typename Message>
        void doLog(LOG_LEVEL level, const Message message) {
            logger.log(
                level,
                DnApp::Common::Strings::format(
                    "[%s] %s",
                    Logger::logLevelToString(level),
                    message
                ).get()
            );
        }
    };

    static_assert(!std::is_abstract<PrependLogLevelLogger>());
}
