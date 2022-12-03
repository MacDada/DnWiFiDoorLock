#pragma once

#include <type_traits>

#include "DnApp/Arduino/Logger/Logger.h"
#include "DnWiFiDoorLock/Tools.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class LogLevelThresholdFilteringLogger final: public DnApp::Arduino::Logger::Logger {
    public:
        // required because otherwise our log() methods hide base class declarations
        using Logger::log;

        explicit LogLevelThresholdFilteringLogger(
            Logger &logger,
            const Logger::LOG_LEVEL threshold = Logger::LOG_LEVEL::DEBUG
        ):
            logger(logger),
            threshold(threshold) {
        };

        LOG_LEVEL getThreshold() const {
            return threshold;
        }

        void setThreshold(LOG_LEVEL threshold) {
            this->threshold = threshold;
        }

        void log(LOG_LEVEL level, const char *message) override {
            doLog(level, message);
        };

        void log(LOG_LEVEL level, char *message) override {
            doLog(level, message);
        };
    private:
        Logger &logger;

        Logger::LOG_LEVEL threshold;

        template <typename MessageType>
        void doLog(LOG_LEVEL level, const MessageType message) {
            if (level >= threshold) {
                logger.log(level, message);
            }
        }
    };

    static_assert(!std::is_abstract<LogLevelThresholdFilteringLogger>());

}
