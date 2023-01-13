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
            logger(logger),
            esp(esp) {
        };

        void log(LOG_LEVEL level, const char* message) override {
            doLog(level, message);
        };

        void log(LOG_LEVEL level, char* message) override {
            doLog(level, message);
        };
    private:
        EspClass& esp;

        Logger& logger;

        template<typename MessageType>
        void doLog(LOG_LEVEL level, const MessageType message) const {
            logger.debug(DnApp::Common::Strings::format(
                PSTR("free heap: %d"),
                esp.getFreeHeap()
            ));

            logger.log(level, message);
        }
    };

    static_assert(!std::is_abstract<MemoryDecoratorLogger>());
}
