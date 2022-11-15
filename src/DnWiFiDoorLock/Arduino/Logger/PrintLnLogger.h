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

        void log(const std::unique_ptr<char[]> message) override {
            doLog(message.get());
        }

        void log(const String &message) override {
            doLog(message);
        };

        void log(const char *const message) override {
            doLog(message);
        };

        void log(char *const message) override {
            doLog(message);
        };

    private:
        Printer &printer;

        template <typename MessageType>
        void doLog(const MessageType message) const {
            printer.println(message);
        }
    };

}
