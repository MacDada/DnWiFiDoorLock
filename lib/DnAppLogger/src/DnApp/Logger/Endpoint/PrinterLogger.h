#pragma once

#include "DnApp/Logger/Logger.h"

namespace DnApp::Logger::Endpoint {
    template<typename Printer>
    class PrinterLogger final:
        public DnApp::Logger::Logger {
    public:
        explicit
        PrinterLogger(Printer& printer) noexcept:
            printer{printer} {
        }

        // Required, because otherwise our `log()` methods
        // would hide base class declarations.
        using DnApp::Logger::Logger::log;

        void log(const LOG_LEVEL level, const char* const message) override {
            printer.println(message);
        }
    private:
        Printer& printer;
    };
}
