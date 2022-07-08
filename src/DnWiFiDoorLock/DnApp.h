#pragma once

#include "config.h"
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

        DnHttpController doorLockWebController = DnHttpController(hardware, doorLock);

        ESP8266WebServer espServer = ESP8266WebServer(WEB_SERVER_PORT);

        DnHttpServer server = DnHttpServer(
            espServer,
            WEB_SERVER_HOST_NAME,
            WEB_SERVER_PORT,
            doorLockWebController
        );

        bool hasLoopStarted = false;

        void informThatTheLoopHasStarted();

        void informTheLoopIsRunning();
    };
}
