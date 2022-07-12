#pragma once

#include <ArduinoOTA.h>
#include "DnWiFiDoorLock/Logger/ArduinoLogger.h"

namespace DnWiFiDoorLock {
    class DnOTAUpdater final {
    public:
        DnOTAUpdater(
            const int port,
            const char *host,
            const char *passwordHash,
            Logger::ArduinoLogger &logger
        );

        void setup();

        void handle();

    private:
        int port;
        const char *host;
        const char *passwordHash;
        Logger::ArduinoLogger *logger;

        const char *otaErrorToString(ota_error_t error);
    };
}
