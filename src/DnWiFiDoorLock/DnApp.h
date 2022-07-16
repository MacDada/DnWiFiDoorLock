#pragma once

#include <Arduino.h>
#include <WebSerial.h>
#include <vector>

#include "config.h"
#include "DnOTAUpdater.h"
#include "ESPAsyncWebServer.h"
#include "DnHardware.h"
#include "DnDoorLock.h"
#include "DnLed.h"
#include "DnWiFi.h"
#include "DnHttpServer.h"
#include "DnHttpController.h"
#include "Logger/HardwareSerialArduinoLogger.h"
#include "Logger/WebSerialArduinoLogger.h"
#include "Logger/MultipleLoggersArduinoLogger.h"

namespace DnWiFiDoorLock {

    class DnApp final {
    public:
        void onSetup();

        void onLoop();

    private:
        DnHardware hardware;

        Logger::HardwareSerialArduinoLogger hardwareSerialLogger = Logger::HardwareSerialArduinoLogger(Serial);

        Logger::WebSerialArduinoLogger webSerialLogger = Logger::WebSerialArduinoLogger(WebSerial);

        std::vector<Logger::ArduinoLogger *> loggers = {&hardwareSerialLogger, &webSerialLogger};

        Logger::MultipleLoggersArduinoLogger logger = Logger::MultipleLoggersArduinoLogger{loggers};

        DnDoorLock doorLock;

        DnLed builtInLed = DnLed(hardware, DnHardware::BUILT_IN_LED_PIN);

        DnWiFi wiFi = DnWiFi(
            WIFI_SSID,
            WIFI_PASSWORD,
            builtInLed,
            // WebSerial(Logger) cannot be injected, runtime crash for some reason
            hardwareSerialLogger
        );

        DnOTAUpdater otaUpdater = DnOTAUpdater(
            OTA_UPDATE_PORT,
            OTA_UPDATE_HOST,
            OTA_UPDATE_PASSWORD_MD5,
            logger
        );

        DnHttpController doorLockWebController = DnHttpController(hardware, doorLock);

        AsyncWebServer espServer = AsyncWebServer(WEB_SERVER_PORT);

        DnHttpServer server = DnHttpServer(
            espServer,
            WEB_SERVER_HOST_NAME,
            WEB_SERVER_PORT,
            doorLockWebController,
            logger
        );

        bool hasLoopStarted = false;

        void informThatTheLoopHasStarted();

        void informTheLoopIsRunning();

        void onWebSerialIncoming(uint8_t *message, size_t messageLength);
    };

}
