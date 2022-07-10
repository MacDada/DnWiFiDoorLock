#pragma once

#include <Arduino.h>
#include "Logger.h"

namespace DnWiFiDoorLock::Logger {

    class ArduinoLogger: public Logger {
    public:
        virtual void log(const String &m) = 0;
    };

}
