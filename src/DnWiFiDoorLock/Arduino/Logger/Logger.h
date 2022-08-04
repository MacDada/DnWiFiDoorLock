#pragma once

#include <functional>

#include <Arduino.h>

#include "DnWiFiDoorLock/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class Logger: public DnWiFiDoorLock::Logger::Logger {
    public:
        virtual void log(const String &message) = 0;

        virtual void log(std::unique_ptr<char[]> message) override = 0;

        virtual void log(const char *message) override = 0;

        virtual void log(char *message) override = 0;

        virtual void log(int message) override = 0;

        virtual void log(double message) override = 0;

        virtual void log(float message) override = 0;
    };

    using LoggerReference = std::reference_wrapper<Logger>;

}
