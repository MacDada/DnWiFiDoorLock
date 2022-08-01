#include "MultipleLoggersLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    MultipleLoggersLogger::MultipleLoggersLogger(
        const std::vector<Logger *> &loggers
    ):
        loggers(loggers) {
    }

    void MultipleLoggersLogger::log(const String &m) {
        // todo: maybe macro to generate those methods? since i think templates cant do that
        doLog(m);
    }

    void MultipleLoggersLogger::log(const char *m) {
        doLog(m);
    }

    void MultipleLoggersLogger::log(char *m) {
        doLog(m);
    }

    void MultipleLoggersLogger::log(int m) {
        doLog(m);
    }

    void MultipleLoggersLogger::log(double m) {
        doLog(m);
    }

    void MultipleLoggersLogger::log(float m) {
        doLog(m);
    }

}
