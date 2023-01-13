#include "MultipleLoggersLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    MultipleLoggersLogger::MultipleLoggersLogger(
        const std::vector<std::reference_wrapper<Logger>>& loggers
    ):
        loggers(loggers) {
    }

    void MultipleLoggersLogger::log(LOG_LEVEL level, char* message) {
        doLog(level, message);
    }

    void MultipleLoggersLogger::log(LOG_LEVEL level, const char* message) {
        // todo: DRY those methods?
        //       * maybe macro to generate those methods? since i think templates cant do that
        //       * or maybe std::any?
        //       * or maybe i can define it somehow in the base class and get rid of the template functions?
        doLog(level, message);
    }

}
