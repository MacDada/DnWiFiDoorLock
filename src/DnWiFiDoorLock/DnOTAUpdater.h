#pragma once

#include <ArduinoOTA.h>

namespace DnWiFiDoorLock {
    class DnOTAUpdater {
    public:
        DnOTAUpdater(const int port, const char *host, const char *passwordHash);

        void setup();

        void handle();

    private:
        int port;
        const char *host;
        const char *passwordHash;

        const char *otaErrorToString(ota_error_t error);
    };
}
