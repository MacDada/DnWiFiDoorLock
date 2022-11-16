#include "MultipleLoggersLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    MultipleLoggersLogger::MultipleLoggersLogger(
        const std::vector<std::reference_wrapper<Logger>> &loggers
    ):
        loggers(loggers) {
    }

    void MultipleLoggersLogger::log(LOG_LEVEL level, const String &message) {
        // todo: DRY those methods?
        //       * maybe macro to generate those methods? since i think templates cant do that
        //       * or maybe std::any?
        doLog(level, message);
    }

    void MultipleLoggersLogger::log(LOG_LEVEL level, std::unique_ptr<char[]> message) {
        doLog(level, message.get());
    }

    void MultipleLoggersLogger::log(LOG_LEVEL level, const char *message) {
        doLog(level, message);
    }

    void MultipleLoggersLogger::log(LOG_LEVEL level, char *message) {
        doLog(level, message);
    }

}
