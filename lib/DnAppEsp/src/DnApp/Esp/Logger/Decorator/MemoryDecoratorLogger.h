#pragma once

#include <type_traits>

#include <Esp.h>
#include <WString.h>

#include "DnApp/Logger/Logger.h"
#include "DnApp/Common/Strings.h"

namespace DnApp::Esp::Logger::Decorator {
    class MemoryDecoratorLogger final:
        public DnApp::Logger::Logger {
    public:
        // required because otherwise our log() methods hide base class declarations
        using DnApp::Logger::Logger::log;

        explicit
        MemoryDecoratorLogger(EspClass& esp, Logger& logger):
            esp(esp),
            logger{logger} {
        };

        void log(const LOG_LEVEL level, const char* const message) override {
            logger.debug(DnApp::Common::Strings::format(
                PSTR("free heap: %d"),
                esp.getFreeHeap()
            ));

            logger.log(level, message);
        };
    private:
        EspClass& esp;

        Logger& logger;
    };

    static_assert(!std::is_abstract<MemoryDecoratorLogger>());
}
