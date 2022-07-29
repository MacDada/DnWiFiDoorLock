#pragma once

#include <type_traits>

#include <ArduinoOTA.h>

#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Logger/ArduinoLogger.h"
#include "DnWiFiDoorLock/Tools.h"

namespace DnWiFiDoorLock {

    class OTAUpdater final: public Arduino::SetupAndLoopAware {
    public:
        OTAUpdater(
            const int port,
            const char *host,
            const char *passwordHash,
            Logger::ArduinoLogger &logger
        );

        void onSetup() override;

        void onLoop() override;

    private:
        int port;

        const char *host;

        const char *passwordHash;

        Logger::ArduinoLogger &logger;

        const char *otaErrorToString(ota_error_t error);
    };

    static_assert(!std::is_abstract<OTAUpdater>());

}
