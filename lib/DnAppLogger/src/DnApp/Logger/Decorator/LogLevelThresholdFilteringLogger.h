#pragma once

#include <type_traits>

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Decorator {
    class LogLevelThresholdFilteringLogger final:
        public Logger {
    public:
        // Required, because otherwise our `log()` methods
        // would hide base class declarations.
        using Logger::log;

        explicit
        LogLevelThresholdFilteringLogger(
            Logger& logger,
            const Logger::LOG_LEVEL threshold = Logger::LOG_LEVEL::DEBUG
        ) noexcept:
            logger{logger},
            threshold{threshold} {
        }

        LOG_LEVEL getThreshold() const {
            return threshold;
        }

        void setThreshold(const LOG_LEVEL newThreshold) {
            threshold = newThreshold;
        }

        void log(const LOG_LEVEL level, const char* const message) override {
            if (level >= threshold) {
                logger.log(level, message);
            }
        };
    private:
        Logger& logger;

        Logger::LOG_LEVEL threshold;
    };

    static_assert(!std::is_abstract<LogLevelThresholdFilteringLogger>());
}
