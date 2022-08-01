#pragma once

#include <vector>

#include <Arduino.h>

#include "DnWiFiDoorLock/Arduino/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class MultipleLoggersLogger final: public Logger {
    public:
        explicit MultipleLoggersLogger(const std::vector<Logger *> &loggers);

        void log(const String &m) override;

        void log(const char *m) override;

        void log(char *m) override;

        void log(int m) override;

        void log(double m) override;

        void log(float m) override;

    private:
        const std::vector<Logger *> &loggers;

        template <typename MessageType>
        void doLog(MessageType m) {
            for (auto &logger : loggers) {
                logger->log(m);
            }
        }
    };

    static_assert(!std::is_abstract<MultipleLoggersLogger>());

}
