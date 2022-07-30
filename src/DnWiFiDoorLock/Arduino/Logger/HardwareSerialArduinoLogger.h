#pragma once

#include <Arduino.h>

#include "DnWiFiDoorLock/Arduino/Logger/ArduinoLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class HardwareSerialArduinoLogger final: public ArduinoLogger {
    public:
        explicit HardwareSerialArduinoLogger(HardwareSerial &serial);

        void log(const String &m) override;

        void log(const char *m) override;

        void log(char *m) override;

        void log(int m) override;

        void log(double m) override;

        void log(float m) override;

    private:
        HardwareSerial &serial;
    };

    static_assert(!std::is_abstract<HardwareSerialArduinoLogger>());

}
