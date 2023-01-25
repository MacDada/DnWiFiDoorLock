#pragma once

#include <type_traits>

#include <ArduinoOTA.h>
#include <WString.h>

#include "DnApp/Common/Strings.h"
#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino {
    class OTAUploaderSetupAndLoopAware final:
        public DnWiFiDoorLock::Arduino::SetupAndLoopAware {
    public:
        explicit
        OTAUploaderSetupAndLoopAware(
            const int port,
            const char* const hostname,
            const char* const passwordHash,
            DnApp::Arduino::Logger::WithArduinoStringLogger& logger
        ):
            port{port},
            hostname{hostname},
            passwordHash{passwordHash},
            logger{logger} {
        }

        void onSetup() override {
            ArduinoOTA.setPort(port);
            ArduinoOTA.setHostname(hostname);
            ArduinoOTA.setPasswordHash(passwordHash);

            ArduinoOTA.onStart([&]() {
                String message{PSTR("Starting the OTA update of the ")};

                if (ArduinoOTA.getCommand() == U_FLASH) {
                    message += PSTR("sketch!");
                } else { // U_FS
                    message += PSTR("filesystem!");
                }

                // NOTE: if updating FS this would be the place to unmount FS using FS.end()
                logger.warning(message);
            });

            ArduinoOTA.onEnd([&]() {
                logger.warning(PSTR("OTA update finished!"));
            });

            ArduinoOTA.onProgress([&](const unsigned int progress, const unsigned int total) {
                logger.warning(DnApp::Common::Strings::format(
                    PSTR("Progress: %u%%"),
                    progress / (total / 100)
                ));
            });

            ArduinoOTA.onError([&](const ota_error_t error) {
                logger.error(DnApp::Common::Strings::format(
                    PSTR("OTA update error[%u]: %s"),
                    error,
                    otaErrorToString(error)
                ));
            });

            ArduinoOTA.begin();
        }

        void onLoop() override {
            ArduinoOTA.handle();
        }
    private:
        const int port;

        const char* const hostname;

        const char* const passwordHash;

        DnApp::Arduino::Logger::WithArduinoStringLogger& logger;

        const char* otaErrorToString(const ota_error_t error) const {
            switch (error) {
                case OTA_AUTH_ERROR:
                    return PSTR("OTA_AUTH_ERROR");
                case OTA_BEGIN_ERROR:
                    return PSTR("OTA_BEGIN_ERROR");
                case OTA_CONNECT_ERROR:
                    return PSTR("OTA_CONNECT_ERROR");
                case OTA_RECEIVE_ERROR:
                    return PSTR("OTA_RECEIVE_ERROR");
                case OTA_END_ERROR:
                    return PSTR("OTA_END_ERROR");
                default:
                    return PSTR("OTA_UNKNOWN_ERROR");
            }
        }
    };

    static_assert(!std::is_abstract<OTAUploaderSetupAndLoopAware>());
}
