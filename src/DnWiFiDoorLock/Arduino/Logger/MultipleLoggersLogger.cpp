#include "MultipleLoggersLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    MultipleLoggersLogger::MultipleLoggersLogger(
        const std::vector<Logger *> &loggers
    ):
        loggers(loggers) {
    }

    void MultipleLoggersLogger::log(const String &m) {
        // todo: get rid of copy–paste
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

    void MultipleLoggersLogger::log(const char *m) {
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

    void MultipleLoggersLogger::log(char *m) {
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

    void MultipleLoggersLogger::log(int m) {
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

    void MultipleLoggersLogger::log(double m) {
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

    void MultipleLoggersLogger::log(float m) {
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

}
