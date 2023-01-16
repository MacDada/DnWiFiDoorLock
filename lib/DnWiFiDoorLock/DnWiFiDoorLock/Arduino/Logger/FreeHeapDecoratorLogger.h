#pragma once

#include <type_traits>

#include <Esp.h>
#include <WString.h>

#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Common/Strings.h"

namespace DnWiFiDoorLock::Arduino::Logger {
    class FreeHeapDecoratorLogger final:
        public DnApp::Arduino::Logger::WithArduinoStringLogger {
    public:
        // required because otherwise our log() methods hide base class declarations
        using DnApp::Arduino::Logger::WithArduinoStringLogger::log;

        explicit
        FreeHeapDecoratorLogger(EspClass& esp, WithArduinoStringLogger& logger):
            logger{logger},
            esp{esp} {
        };

        void log(LOG_LEVEL level, const char* message) override {
            doLog(level, message);
        };

        void log(LOG_LEVEL level, char* message) override {
            doLog(level, message);
        };
    private:
        EspClass& esp;

        WithArduinoStringLogger& logger;

        template<typename MessageType>
        void doLog(LOG_LEVEL level, const MessageType message) const {
            logger.debug(DnApp::Common::Strings::format(
                PSTR("free heap: %d"),
                esp.getFreeHeap()
            ));

            logger.log(level, message);
        }
    };

    static_assert(!std::is_abstract<FreeHeapDecoratorLogger>());
}
