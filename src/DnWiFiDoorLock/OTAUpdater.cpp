#include "OTAUpdater.h"
#include "Tools.h"

namespace DnWiFiDoorLock {

    OTAUpdater::OTAUpdater(
        const int port,
        const char *host,
        const char *passwordHash,
        Logger::ArduinoLogger &logger
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
            logger.log("Start updating " + type);
        });

        ArduinoOTA.onEnd([&]() {
            logger.log("End");
        });

        ArduinoOTA.onProgress([&](unsigned int progress, unsigned int total) {
            logger.log(Tools::format("Progress: %u%%", progress / (total / 100)));
        });

        ArduinoOTA.onError([&](ota_error_t error) {
            logger.log(Tools::format("Error[%u]: %s", error, otaErrorToString(error)));
        });

        ArduinoOTA.begin();
    }

    void OTAUpdater::onLoop() {
        ArduinoOTA.handle();
    }

    // todo: `const ota_error_t &error`?
    const char *OTAUpdater::otaErrorToString(ota_error_t error) {
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
