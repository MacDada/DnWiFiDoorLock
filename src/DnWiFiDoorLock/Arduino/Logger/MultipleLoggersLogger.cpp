#include "MultipleLoggersLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    MultipleLoggersLogger::MultipleLoggersLogger(
        const std::vector<std::reference_wrapper<Logger>> &loggers
    ):
        loggers(loggers) {
    }

    void MultipleLoggersLogger::log(const String &message) {
        // todo: DRY those methods?
        //       * maybe macro to generate those methods? since i think templates cant do that
        //       * or maybe std::any?
        doLog(message);
    }

    void MultipleLoggersLogger::log(const std::unique_ptr<char[]> message) {
        doLog(message.get());
    }

    void MultipleLoggersLogger::log(const char *const message) {
        doLog(message);
    }

    void MultipleLoggersLogger::log(char *const message) {
        doLog(message);
    }

}
