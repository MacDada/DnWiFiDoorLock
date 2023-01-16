#pragma once

#include <type_traits>

#include <ArduinoOTA.h>
#include <WString.h>

#include "DnApp/Common/Strings.h"
#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class OTAUpdater final:
        public DnWiFiDoorLock::Arduino::SetupAndLoopAware {
    public:
        OTAUpdater(
            int port,
            const char* host,
            const char* passwordHash,
            DnApp::Arduino::Logger::WithArduinoStringLogger& logger
        );

        void onSetup() override;

        void onLoop() override;
    private:
        const int port;

        const char* const host;

        const char* const passwordHash;

        DnApp::Arduino::Logger::WithArduinoStringLogger& logger;

        const char* otaErrorToString(ota_error_t error) const;
    };

    static_assert(!std::is_abstract<OTAUpdater>());
}
