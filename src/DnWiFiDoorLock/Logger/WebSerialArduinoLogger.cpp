#include "WebSerialArduinoLogger.h"

namespace DnWiFiDoorLock::Logger {

    WebSerialArduinoLogger::WebSerialArduinoLogger(
        WebSerialClass &serial
    ):
        serial(serial) {
    }

    void WebSerialArduinoLogger::log(const String &m) {
        serial.println(m);
    }

    void WebSerialArduinoLogger::log(const char *m) {
        serial.println(m);
    }

    void WebSerialArduinoLogger::log(char *m) {
        serial.println(m);
    }

    void WebSerialArduinoLogger::log(int m) {
        serial.println(m);
    }

    void WebSerialArduinoLogger::log(double m) {
        serial.println(m);
    }

    void WebSerialArduinoLogger::log(float m) {
        serial.println(m);
    }

}
