#include "HardwareSerialArduinoLogger.h"

/**
 * todo: templates so i don't repeat myself?
 * https://discord.com/channels/583251190591258624/742849025191051326/995793195977945228
 *
 * template <typename T>
 * HardwareSerialArduinoLogger::log(const T& m) {
 *    serial->println(m);
 * }
 * */

/**
 * todo: accept to log any kind of thingy?
 * https://discord.com/channels/583251190591258624/742849025191051326/995776740892885112
 *
 * typeID(T).name()
 */

namespace DnWiFiDoorLock::Arduino::Logger {

    HardwareSerialArduinoLogger::HardwareSerialArduinoLogger(
        HardwareSerial &serial
    ):
        serial(serial) {
    }

    void HardwareSerialArduinoLogger::log(const String &m) {
        serial.println(m);
    }

    void HardwareSerialArduinoLogger::log(const char *m) {
        serial.println(m);
    }

    void HardwareSerialArduinoLogger::log(char *m) {
        serial.println(m);
    }

    void HardwareSerialArduinoLogger::log(int m) {
        serial.println(m);
    }

    void HardwareSerialArduinoLogger::log(double m) {
        serial.println(m);
    }

    void HardwareSerialArduinoLogger::log(float m) {
        serial.println(m);
    }

}
