#pragma once

#include <vector>

#include <Arduino.h>

#include "DnWiFiDoorLock/Arduino/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class MultipleLoggersLogger final: public Logger {
    public:
        explicit MultipleLoggersLogger(const std::vector<Logger *> &loggers);

        void log(const String &message) override;

        void log(const char *message) override;

        void log(char *message) override;

        void log(int message) override;

        void log(double message) override;

        void log(float message) override;

    private:
        const std::vector<Logger *> &loggers;

        template <typename MessageType>
        void doLog(MessageType message) {
            for (auto &logger : loggers) {
                logger->log(message);
            }
        }
    };

    static_assert(!std::is_abstract<MultipleLoggersLogger>());

}
