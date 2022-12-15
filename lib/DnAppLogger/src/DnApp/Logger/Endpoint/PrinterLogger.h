#pragma once

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Endpoint {
    template <typename Printer>
    class PrinterLogger final: public DnApp::Logger::Logger {
    public:
        using DnApp::Logger::Logger::log;

        explicit PrinterLogger (Printer &printer) noexcept:
            printer(printer) {
        }

        void log(LOG_LEVEL level, char *message) override {
            printer.println(message);
        }

        void log(LOG_LEVEL level, const char *message) override {
            printer.println(message);
        }
    private:
        Printer &printer;
    };
}
