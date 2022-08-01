#pragma once

#include <Arduino.h>

#include "DnWiFiDoorLock/Arduino/Logger/Logger.h"

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

    template <typename Printer>
    class PrintLnLogger final: public Logger {
    public:
        explicit PrintLnLogger(
            Printer &printer
        ):
            printer(printer) {
        };

        void log(const String &m) override {
            doLog(m);
        };

        void log(const char *m) override {
            doLog(m);
        };

        void log(char *m) override {
            doLog(m);
        };

        void log(int m) override {
            doLog(m);
        };

        void log(double m) override {
            doLog(m);
        };

        void log(float m) override {
            doLog(m);
        };

    private:
        Printer &printer;

        template <typename MessageType>
        void doLog(MessageType m) {
            printer.println(m);
        }
    };

}
