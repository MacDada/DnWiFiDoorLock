#include "Logger.h"

namespace DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial {

    Logger::Logger(
        WebSerialClass &serial
    ):
        serial(serial) {
    }

    void Logger::log(const String &m) {
        serial.println(m);
    }

    void Logger::log(const char *m) {
        serial.println(m);
    }

    void Logger::log(char *m) {
        serial.println(m);
    }

    void Logger::log(int m) {
        serial.println(m);
    }

    void Logger::log(double m) {
        serial.println(m);
    }

    void Logger::log(float m) {
        serial.println(m);
    }

}
