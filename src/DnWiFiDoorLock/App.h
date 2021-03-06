#pragma once

#include <array>
#include <vector>

#include <Arduino.h>
#include <WebSerial.h>

#include "Arduino/Esp8266/EspAsyncWebServer/WebSerial/SetupAndLoopAwareWebSerial.h"
#include "Arduino/HardwareSerialSetup.h"
#include "Arduino/LoopIndicator.h"
#include "Arduino/SetupAndLoopAware.h"
#include "config.h"
#include "OTAUpdater.h"
#include "ESPAsyncWebServer.h"
#include "Hardware.h"
#include "DoorLock.h"
#include "Led.h"
#include "WiFi.h"
#include "HttpServer.h"
#include "HttpController.h"
#include "Logger/HardwareSerialArduinoLogger.h"
#include "Logger/WebSerialArduinoLogger.h"
#include "Logger/MultipleLoggersArduinoLogger.h"

namespace DnWiFiDoorLock {

using Arduino::Esp8266::EspAsyncWebServer::WebSerial::SetupAndLoopAwareWebSerial;

class App final: public Arduino::SetupAndLoopAware {
    public:
        void onSetup() override;

        void onLoop() override;

    private:
        Hardware hardware;

        Logger::HardwareSerialArduinoLogger hardwareSerialLogger = Logger::HardwareSerialArduinoLogger(Serial);

        Logger::WebSerialArduinoLogger webSerialLogger = Logger::WebSerialArduinoLogger(WebSerial);

        std::vector<Logger::ArduinoLogger *> loggers = {&hardwareSerialLogger, &webSerialLogger};

        Logger::MultipleLoggersArduinoLogger logger = Logger::MultipleLoggersArduinoLogger{loggers};

        DoorLock doorLock;

        Led builtInLed = Led(hardware, Hardware::BUILT_IN_LED_PIN);

        WiFi wiFi = WiFi(
            WIFI_SSID,
            WIFI_PASSWORD,
            builtInLed,
            // WebSerial(Logger) cannot be injected, runtime crash for some reason
            hardwareSerialLogger,
            hardware,
            ::WiFi
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

        Arduino::HardwareSerialSetup hardwareSerialSetup = Arduino::HardwareSerialSetup(
            Serial,
            hardware,
            SERIAL_BITS_PER_SECOND
        );

        SetupAndLoopAwareWebSerial setupAndLoopAwareWebSerial = SetupAndLoopAwareWebSerial(WebSerial, espServer);

        Arduino::LoopIndicator loopIndicator = Arduino::LoopIndicator(builtInLed, logger);

        std::array<Arduino::SetupAndLoopAware *, 6> setupAndLoopAwares = {
            &hardwareSerialSetup,
            &wiFi,
            &loopIndicator,
            &setupAndLoopAwareWebSerial,
            &otaUpdater,
            &server
        };
    };

}
