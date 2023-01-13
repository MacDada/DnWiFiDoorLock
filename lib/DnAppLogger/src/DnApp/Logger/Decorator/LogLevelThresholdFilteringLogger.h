#pragma once

#include <type_traits>

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Decorator {
    class LogLevelThresholdFilteringLogger final:
        public DnApp::Logger::Logger {
    public:
        // required because otherwise our log() methods hide base class declarations
        using Logger::log;

        explicit
        LogLevelThresholdFilteringLogger(
            Logger& logger,
            const Logger::LOG_LEVEL threshold = Logger::LOG_LEVEL::DEBUG
        ) noexcept:
            logger(logger),
            threshold(threshold) {
        }

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
        DnApp::Logger::Logger& logger;

        // todo: CLion complaining about shadowing?
        //       https://discord.com/channels/583251190591258624/1063376138510028851/1063376138510028851
        Logger::LOG_LEVEL threshold;

        template<typename Message>
        void doLog(LOG_LEVEL level, const Message message) {
            if (level >= threshold) {
                logger.log(level, message);
            }
        }
    };

    static_assert(!std::is_abstract<LogLevelThresholdFilteringLogger>());
}
