#pragma once

#include <type_traits>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {
    class LogLevelThresholdFilteringLogger final:
        public DnApp::Arduino::Logger::WithArduinoStringLogger {
    public:
        // required because otherwise our log() methods hide base class declarations
        using WithArduinoStringLogger::log;

        explicit
        LogLevelThresholdFilteringLogger(
            WithArduinoStringLogger& logger,
            const WithArduinoStringLogger::LOG_LEVEL threshold = WithArduinoStringLogger::LOG_LEVEL::DEBUG
        ):
            logger{logger},
            threshold{threshold} {
        };

        LOG_LEVEL getThreshold() const {
            return threshold;
        }

        void setThreshold(LOG_LEVEL threshold) {
            this->threshold = threshold;
        }

        void log(LOG_LEVEL level, const char* message) override {
            doLog(level, message);
        };

        void log(LOG_LEVEL level, char* message) override {
            doLog(level, message);
        };
    private:
        WithArduinoStringLogger& logger;

        WithArduinoStringLogger::LOG_LEVEL threshold;

        template<typename Message>
        void doLog(LOG_LEVEL level, const Message message) {
            if (level >= threshold) {
                logger.log(level, message);
            }
        }
    };

    static_assert(!std::is_abstract<LogLevelThresholdFilteringLogger>());
}
