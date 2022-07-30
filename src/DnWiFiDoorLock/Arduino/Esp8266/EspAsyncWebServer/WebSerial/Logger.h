#pragma once

#include <Arduino.h>
#include <WebSerial.h>

#include "DnWiFiDoorLock/Logger/ArduinoLogger.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial {

    class Logger final: public DnWiFiDoorLock::Logger::ArduinoLogger {
    public:
        explicit Logger(WebSerialClass &serial);

        void log(const String &m) override;

        void log(const char *m) override;

        void log(char *m) override;

        void log(int m) override;

        void log(double m) override;

        void log(float m) override;

    private:
        WebSerialClass &serial;
    };

    static_assert(!std::is_abstract<Logger>());

}
