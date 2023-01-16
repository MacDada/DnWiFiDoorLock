#pragma once

#include <Arduino.h>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {
    template<typename Printer>
    class PrintLnLogger final:
        public DnApp::Arduino::Logger::WithArduinoStringLogger {
    public:
        explicit
        PrintLnLogger(
            Printer& printer
        ):
            printer{printer} {
        };

        using WithArduinoStringLogger::log;

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
            printer.print(WithArduinoStringLogger::logLevelToString(level));
            printer.print("] ");
            printer.println(message);
        }
    };
}
