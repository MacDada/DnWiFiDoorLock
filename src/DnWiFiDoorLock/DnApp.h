#pragma once

#include "config.h"
#include "DnOTAUpdater.h"
#include "ESPAsyncWebServer.h"
#include <WebSerial.h>
#include "DnHardware.h"
#include "DnDoorLock.h"
#include "DnLed.h"
#include "DnWiFi.h"
#include "DnHttpServer.h"
#include "DnHttpController.h"

namespace DnWiFiDoorLock {
    class DnApp {
    public:
        void onSetup();

        void onLoop();

    private:
        DnHardware hardware;

        DnDoorLock doorLock;

        DnLed builtInLed = DnLed(hardware, DnHardware::BUILT_IN_LED_PIN);

        DnWiFi wiFi = DnWiFi(WIFI_SSID, WIFI_PASSWORD, builtInLed);

        DnOTAUpdater otaUpdater = DnOTAUpdater(OTA_UPDATE_PORT, OTA_UPDATE_HOST, OTA_UPDATE_PASSWORD_MD5);

        DnHttpController doorLockWebController = DnHttpController(hardware, doorLock);

        AsyncWebServer espServer = AsyncWebServer(WEB_SERVER_PORT);

        DnHttpServer server = DnHttpServer(
            espServer,
            WEB_SERVER_HOST_NAME,
            WEB_SERVER_PORT,
            doorLockWebController
        );

        bool hasLoopStarted = false;

        void informThatTheLoopHasStarted();

        void informTheLoopIsRunning();

        void onWebSerialIncoming(uint8_t *message, size_t messageLength);
    };
}
