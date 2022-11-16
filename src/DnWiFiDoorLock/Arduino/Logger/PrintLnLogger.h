#pragma once

#include <Arduino.h>

#include "DnWiFiDoorLock/Arduino/Logger/Logger.h"

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

        using Logger::log;

        void log(LOG_LEVEL level, char *message) override {
            doLog(level, message);
        };

        void log(LOG_LEVEL level, const char *message) override {
            doLog(level, message);
        };

    private:
        Printer &printer;

        template <typename MessageType>
        void doLog(LOG_LEVEL level, const MessageType message) const {
            printer.print("[");
            printer.print(LOG_LEVELS[static_cast<int>(level)]);
            printer.print("] ");
            printer.println(message);
        }
    };

}
