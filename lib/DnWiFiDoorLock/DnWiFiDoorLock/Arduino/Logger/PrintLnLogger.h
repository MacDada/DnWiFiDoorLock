#pragma once

#include <Arduino.h>

#include "DnApp/Arduino/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Logger {
    template<typename Printer>
    class PrintLnLogger final:
        public DnApp::Arduino::Logger::Logger {
    public:
        explicit
        PrintLnLogger(
            Printer& printer
        ):
            printer{printer} {
        };

        using Logger::log;

        void log(LOG_LEVEL level, char* message) override {
            doLog(level, message);
        };

        void log(LOG_LEVEL level, const char* message) override {
            doLog(level, message);
        };
    private:
        Printer& printer;

        template<typename MessageType>
        void doLog(LOG_LEVEL level, const MessageType message) const {
            printer.print("[");
            printer.print(Logger::logLevelToString(level));
            printer.print("] ");
            printer.println(message);
        }
    };
}
