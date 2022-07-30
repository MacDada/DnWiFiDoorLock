#pragma once

#include <Arduino.h>

#include "DnWiFiDoorLock/Arduino/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class HardwareSerialLogger final: public Logger {
    public:
        explicit HardwareSerialLogger(HardwareSerial &serial);

        void log(const String &m) override;

        void log(const char *m) override;

        void log(char *m) override;

        void log(int m) override;

        void log(double m) override;

        void log(float m) override;

    private:
        HardwareSerial &serial;
    };

    static_assert(!std::is_abstract<HardwareSerialLogger>());

}
