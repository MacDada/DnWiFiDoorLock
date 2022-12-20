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
            String type;

            if (ArduinoOTA.getCommand() == U_FLASH) {
                type = "sketch";
            } else { // U_FS
                type = "filesystem";
            }

            // NOTE: if updating FS this would be the place to unmount FS using FS.end()
            logger.info("Start updating " + type);
        });

        ArduinoOTA.onEnd([&]() {
            logger.info("End");
        });

        ArduinoOTA.onProgress([&](const unsigned int progress, const unsigned int total) {
            logger.log(
                DnApp::Arduino::Logger::Logger::LOG_LEVEL::INFO,
                DnApp::Common::Strings::format(
                    "Progress: %u%%",
                    progress / (total / 100)
                )
            );
        });

        ArduinoOTA.onError([&](const ota_error_t error) {
            logger.log(
                DnApp::Arduino::Logger::Logger::LOG_LEVEL::ERROR,
                DnApp::Common::Strings::format(
                    "Error[%u]: %s",
                    error,
                    otaErrorToString(error)
                )
            );
        });

        ArduinoOTA.begin();
    }

    void OTAUpdater::onLoop() {
        ArduinoOTA.handle();
    }

    const char *OTAUpdater::otaErrorToString(const ota_error_t error) const {
        switch (error) {
            case OTA_AUTH_ERROR:
                return "OTA_AUTH_ERROR";
            case OTA_BEGIN_ERROR:
                return "OTA_BEGIN_ERROR";
            case OTA_CONNECT_ERROR:
                return "OTA_CONNECT_ERROR";
            case OTA_RECEIVE_ERROR:
                return "OTA_RECEIVE_ERROR";
            case OTA_END_ERROR:
                return "OTA_END_ERROR";
            default:
                return "OTA_UNKNOWN_ERROR";
        }
    }
}
