#include "OTAUpdater.h"

namespace DnWiFiDoorLock::Arduino {
    OTAUpdater::OTAUpdater(
        const int port,
        const char *const host,
        const char *const passwordHash,
        DnApp::Arduino::Logger::Logger &logger
    ):
        port(port),
        host(host),
        passwordHash(passwordHash),
        logger(logger) {
    }

    void OTAUpdater::onSetup() {
        ArduinoOTA.setPort(port);
        ArduinoOTA.setHostname(host);
        ArduinoOTA.setPasswordHash(passwordHash);

        ArduinoOTA.onStart([&]() {
            String message{F("Start updating ")};

            if (ArduinoOTA.getCommand() == U_FLASH) {
                message += F("sketch");
            } else { // U_FS
                message += F("filesystem");
            }

            // NOTE: if updating FS this would be the place to unmount FS using FS.end()
            logger.info(message);
        });

        ArduinoOTA.onEnd([&]() {
            logger.info(F("End"));
        });

        ArduinoOTA.onProgress([&](const unsigned int progress, const unsigned int total) {
            logger.info(DnApp::Common::Strings::format(
                PSTR("Progress: %u%%"),
                progress / (total / 100)
            ));
        });

        ArduinoOTA.onError([&](const ota_error_t error) {
            logger.error(DnApp::Common::Strings::format(
                PSTR("Error[%u]: %s"),
                error,
                otaErrorToString(error)
            ));
        });

        ArduinoOTA.begin();
    }

    void OTAUpdater::onLoop() {
        ArduinoOTA.handle();
    }

    const char *OTAUpdater::otaErrorToString(const ota_error_t error) const {
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
}
