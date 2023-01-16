#include "MultipleLoggersLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    MultipleLoggersLogger::MultipleLoggersLogger(
        const std::vector<std::reference_wrapper<WithArduinoStringLogger>>& loggers
    ):
        loggers{loggers} {
    }

    void MultipleLoggersLogger::log(LOG_LEVEL level, char* message) {
        doLog(level, message);
    }

    void MultipleLoggersLogger::log(LOG_LEVEL level, const char* message) {
        doLog(level, message);
    }

}
