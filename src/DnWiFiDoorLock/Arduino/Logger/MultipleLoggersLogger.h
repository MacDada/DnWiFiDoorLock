#pragma once

#include <functional>
#include <vector>

#include <Arduino.h>

#include "DnWiFiDoorLock/Arduino/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class MultipleLoggersLogger final: public Logger {
    public:
        explicit MultipleLoggersLogger(const std::vector<LoggerReference> &loggers);

        void log(std::unique_ptr<char[]> message) override;

        void log(const String &message) override;

        void log(const char *message) override;

        void log(char *message) override;

    private:
        /**
         * vector cannot store abstract classes as values,
         * but we can store pointers to them
         */
        const std::vector<LoggerReference> &loggers;

        template <typename MessageType>
        void doLog(const MessageType message) const {
            for (const auto &logger : loggers) {
                logger.get().log(message);
            }
        }
    };

    static_assert(!std::is_abstract<MultipleLoggersLogger>());

}
