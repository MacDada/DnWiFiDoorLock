#pragma once

#include <type_traits>

#include "DnWiFiDoorLock/Arduino/Logger/Logger.h"
#include "DnWiFiDoorLock/Tools.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    class FreeHeapDecoratorLogger final: public Logger {
    public:
        // required because otherwise our log() methods hide base class declarations
        using Logger::log;

        explicit FreeHeapDecoratorLogger(Logger &logger):
            logger(logger) {
        };

        void log(LOG_LEVEL level, const char *message) override {
            doLog(level, message);
        };

        void log(LOG_LEVEL level, char *message) override {
            doLog(level, message);
        };
    private:
        Logger &logger;

        template <typename MessageType>
        void doLog(LOG_LEVEL level, const MessageType message) const {
            logger.debug(Tools::format("free heap: %d", system_get_free_heap_size()));
            logger.log(level, message);
        }
    };

    static_assert(!std::is_abstract<FreeHeapDecoratorLogger>());

}
