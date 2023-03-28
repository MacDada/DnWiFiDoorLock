#pragma once

#include <type_traits> // std::is_abstract

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
            logger{logger} {
        }

        auto log(const LOG_LEVEL level, const char* const message) -> void override {
            logger.log(
                level,
                DnApp::Common::Strings::format(
                    "[%s] %s",
                    Logger::logLevelToString(level),
                    message
                ).get()
            );
        };
    private:
        Logger& logger;
    };

    static_assert(!std::is_abstract<PrependLogLevelLogger>());
}
