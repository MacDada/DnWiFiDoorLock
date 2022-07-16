#pragma once

#include <Arduino.h>
#include <WebSerial.h>
#include <vector>

#include "config.h"
#include "OTAUpdater.h"
#include "ESPAsyncWebServer.h"
#include "Hardware.h"
#include "DoorLock.h"
#include "Led.h"
#include "DnWiFi.h"
#include "HttpServer.h"
#include "HttpController.h"
#include "Logger/HardwareSerialArduinoLogger.h"
#include "Logger/WebSerialArduinoLogger.h"
#include "Logger/MultipleLoggersArduinoLogger.h"

namespace DnWiFiDoorLock {

    class App final {
    public:
        void onSetup();

        void onLoop();

    private:
        Hardware hardware;

        Logger::HardwareSerialArduinoLogger hardwareSerialLogger = Logger::HardwareSerialArduinoLogger(Serial);

        Logger::WebSerialArduinoLogger webSerialLogger = Logger::WebSerialArduinoLogger(WebSerial);

        std::vector<Logger::ArduinoLogger *> loggers = {&hardwareSerialLogger, &webSerialLogger};

        Logger::MultipleLoggersArduinoLogger logger = Logger::MultipleLoggersArduinoLogger{loggers};

        DoorLock doorLock;

        Led builtInLed = Led(hardware, Hardware::BUILT_IN_LED_PIN);

        DnWiFi wiFi = DnWiFi(
            WIFI_SSID,
            WIFI_PASSWORD,
            builtInLed,
            // WebSerial(Logger) cannot be injected, runtime crash for some reason
            hardwareSerialLogger
        );

        OTAUpdater otaUpdater = OTAUpdater(
            OTA_UPDATE_PORT,
            OTA_UPDATE_HOST,
            OTA_UPDATE_PASSWORD_MD5,
            logger
        );

        HttpController doorLockWebController = HttpController(hardware, doorLock);

        AsyncWebServer espServer = AsyncWebServer(WEB_SERVER_PORT);

        HttpServer server = HttpServer(
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
