#include "MultipleLoggersLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    MultipleLoggersLogger::MultipleLoggersLogger(
        const std::vector<Logger *> &loggers
    ):
        loggers(loggers) {
    }

    void MultipleLoggersLogger::log(const String &message) {
        // todo: DRY those methods?
        //       * maybe macro to generate those methods? since i think templates cant do that
        //       * or maybe std::any?
        doLog(message);
    }

    void MultipleLoggersLogger::log(const char *message) {
        doLog(message);
    }

    void MultipleLoggersLogger::log(char *message) {
        doLog(message);
    }

    void MultipleLoggersLogger::log(int message) {
        doLog(message);
    }

    void MultipleLoggersLogger::log(double message) {
        doLog(message);
    }

    void MultipleLoggersLogger::log(float message) {
        doLog(message);
    }

}
