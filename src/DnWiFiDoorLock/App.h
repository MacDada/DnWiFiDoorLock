#pragma once

#include <array>
#include <vector>

#include <Arduino.h>
#include <WebSerial.h>

#include "Arduino/Esp8266/EspAsyncWebServer/WebSerial/SetupAndLoopAwareWebSerial.h"
#include "Arduino/Esp8266/WiFi/LoopAwareSignalStrengthLogger.h"
#include "Arduino/HardwareSerialSetup.h"
#include "Arduino/LoopIndicator.h"
#include "Arduino/SetupAndLoopAware.h"
#include "Arduino/ThrottledLoopAware.h"
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

using DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial::SetupAndLoopAwareWebSerial;
using DnWiFiDoorLock::Arduino::Esp8266::WiFi::LoopAwareSignalStrengthLogger;

class App final: public Arduino::SetupAndLoopAware {
    public:
        void onSetup() override;

        void onLoop() override;

    private:
        static const int MILLISECONDS_IN_SECOND = 1000;
        static const int WIFI_STRENGTH_LOGGING_INTERVAL_MILLISECONDS = MILLISECONDS_IN_SECOND;

        static const int LOOP_INDICATOR_LED_TOGGLE_INTERVAL_MILLISECONDS = MILLISECONDS_IN_SECOND;

        Hardware hardware;

        Logger::HardwareSerialArduinoLogger hardwareSerialLogger = Logger::HardwareSerialArduinoLogger(Serial);

        Logger::WebSerialArduinoLogger webSerialLogger = Logger::WebSerialArduinoLogger(WebSerial);

        std::vector<Logger::ArduinoLogger *> loggers = {
            &hardwareSerialLogger,
            &webSerialLogger
        };

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

        LoopAwareSignalStrengthLogger wifiSignalStrengthLogger = LoopAwareSignalStrengthLogger(
            ::WiFi,
            logger
        );

        Arduino::ThrottledLoopAware throttledWiFiSignalStrengthLogger = Arduino::ThrottledLoopAware(
            wifiSignalStrengthLogger,
            hardware,
            WIFI_STRENGTH_LOGGING_INTERVAL_MILLISECONDS
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

        Arduino::ThrottledLoopAware throttledLoopIndicator = Arduino::ThrottledLoopAware(
            loopIndicator,
            hardware,
            LOOP_INDICATOR_LED_TOGGLE_INTERVAL_MILLISECONDS
        );

        std::array<Arduino::SetupAndLoopAware *, 7> setupAndLoopAwares = {
            &hardwareSerialSetup,
            &wiFi,
            &throttledLoopIndicator,
            &setupAndLoopAwareWebSerial,
            &otaUpdater,
            &server,
            &throttledWiFiSignalStrengthLogger
        };
    };

}
