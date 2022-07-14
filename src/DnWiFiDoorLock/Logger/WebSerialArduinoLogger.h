#pragma once

#include <Arduino.h>
#include <WebSerial.h>
#include "ArduinoLogger.h"

namespace DnWiFiDoorLock::Logger {

    class WebSerialArduinoLogger final: public ArduinoLogger {
    public:
        explicit WebSerialArduinoLogger(WebSerialClass &serial);

        void log(const String &m) override;

        void log(const char *m) override;

        void log(char *m) override;

        void log(int m) override;

        void log(double m) override;

        void log(float m) override;

    private:
        WebSerialClass *serial;
    };

    static_assert(!std::is_abstract<WebSerialArduinoLogger>());

}
