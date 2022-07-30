#include "MultipleLoggersArduinoLogger.h"

namespace DnWiFiDoorLock::Arduino::Logger {

    MultipleLoggersArduinoLogger::MultipleLoggersArduinoLogger(
        const std::vector<Logger *> &loggers
    ):
        loggers(loggers) {
    }

    void MultipleLoggersArduinoLogger::log(const String &m) {
        // todo: get rid of copy–paste
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

    void MultipleLoggersArduinoLogger::log(const char *m) {
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

    void MultipleLoggersArduinoLogger::log(char *m) {
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

    void MultipleLoggersArduinoLogger::log(int m) {
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

    void MultipleLoggersArduinoLogger::log(double m) {
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

    void MultipleLoggersArduinoLogger::log(float m) {
        for (auto &logger : loggers) {
            logger->log(m);
        }
    }

}
