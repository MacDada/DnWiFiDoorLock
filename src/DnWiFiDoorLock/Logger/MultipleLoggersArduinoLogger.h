#pragma once

#include <Arduino.h>
#include <vector>

#include "ArduinoLogger.h"

namespace DnWiFiDoorLock::Logger {

    class MultipleLoggersArduinoLogger final: public ArduinoLogger {
    public:
        explicit MultipleLoggersArduinoLogger(const std::vector<ArduinoLogger*> &loggers);

        void log(const String &m) override;

        void log(const char *m) override;

        void log(char *m) override;

        void log(int m) override;

        void log(double m) override;

        void log(float m) override;

    private:
        const std::vector<ArduinoLogger*> &loggers;
    };

    static_assert(!std::is_abstract<MultipleLoggersArduinoLogger>());

}
