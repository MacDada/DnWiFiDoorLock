#pragma once

#include <Arduino.h>

#include "DnWiFiDoorLock/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class Logger: public DnWiFiDoorLock::Logger::Logger {
    public:
        virtual void log(const String &m) = 0;

        virtual void log(const char *m) override = 0;

        virtual void log(char *m) override = 0;

        virtual void log(int m) override = 0;

        virtual void log(double m) override = 0;

        virtual void log(float m) override = 0;
    };

}
