#pragma once

#include <array>
#include <vector>

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>
#include <WebSerial.h>

#include "config.h"

#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/DoorLockController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/ServoController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/WebSerial/SetupAndLoopAwareWebSerial.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/MDNSSetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/WiFi/LoopAwareSignalStrengthLogger.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/WiFi/WiFi.h"
#include "DnWiFiDoorLock/Arduino/DoorLock.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/HardwareSerialSetup.h"
#include "DnWiFiDoorLock/Arduino/Led.h"
#include "DnWiFiDoorLock/Arduino/LoopIndicator.h"
#include "DnWiFiDoorLock/Arduino/OTAUpdater.h"
#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/ThrottledLoopAware.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/ServerSetup.h"
#include "DnWiFiDoorLock/Logger/HardwareSerialArduinoLogger.h"
#include "DnWiFiDoorLock/Logger/WebSerialArduinoLogger.h"
#include "DnWiFiDoorLock/Logger/MultipleLoggersArduinoLogger.h"

namespace DnWiFiDoorLock {

    using DoorLockImpl = DnWiFiDoorLock::Arduino::DoorLock;
    using DnWiFiDoorLock::Arduino::Led;
    using DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::DoorLockController;
    using DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServerSetup;
    using DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServoController;
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

        DnWiFiDoorLock::Arduino::Hardware hardware;

        Logger::HardwareSerialArduinoLogger hardwareSerialLogger = Logger::HardwareSerialArduinoLogger(Serial);

        Logger::WebSerialArduinoLogger webSerialLogger = Logger::WebSerialArduinoLogger(WebSerial);

        std::vector<Logger::ArduinoLogger *> loggers = {
            &hardwareSerialLogger,
            &webSerialLogger
        };

        Logger::MultipleLoggersArduinoLogger logger = Logger::MultipleLoggersArduinoLogger{loggers};

        ::Servo arduinoServo;

        // todo: why the servo does not reach proper 0-180 degree angles by default?
        //      * https://www.arduino.cc/reference/en/libraries/servo/attach/
        //          - the docs say the default pulse should be 544-2400
        //      * the lib actually defaults to 1000-2000 [which sounds like the "industry standard"]
        //          - note when testing: changing the max does not impact the min and vice versa
        //      * the servo's specs: https://download.kamami.pl/p195301-HD-1501MG.pdf
        //          - according to the specs i dont know what to think, but i guess it should be 800-2200?
        //      * verified values that work OK: 500-2500
        //      * setting a smaller range just to be safe
        Arduino::Servo::Servo servo = Arduino::Servo::Servo(arduinoServo, SERVO_PIN, 600, 2400, logger);

        DoorLockImpl doorLock = DoorLockImpl(servo, logger, 0, 180);

        Led builtInLed = Led(hardware, DnWiFiDoorLock::Arduino::Hardware::BUILT_IN_LED_PIN);

        DnWiFiDoorLock::Arduino::Esp82666::WiFi::WiFi wiFi = DnWiFiDoorLock::Arduino::Esp82666::WiFi::WiFi(
            WIFI_SSID,
            WIFI_PASSWORD,
            builtInLed,
            // WebSerial(Logger) cannot be injected, runtime crash for some reason
            hardwareSerialLogger,
            hardware,
            ::WiFi
        );

        Arduino::Esp8266::MDNSSetupAndLoopAware mdns = Arduino::Esp8266::MDNSSetupAndLoopAware(
            MDNS,
            logger,
            WEB_SERVER_HOST_NAME
        );

        DnWiFiDoorLock::Arduino::OTAUpdater otaUpdater = DnWiFiDoorLock::Arduino::OTAUpdater(
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

        DoorLockController doorLockHttpController = DoorLockController(hardware, doorLock);

        // todo: in the end we don't need that, but it is useful for calibration
        ServoController servoHttpController = ServoController(servo, logger);

        AsyncWebServer espServer = AsyncWebServer(WEB_SERVER_PORT);

        ServerSetup server = ServerSetup(
            espServer,
            WEB_SERVER_HOST_NAME,
            WEB_SERVER_PORT,
            doorLockHttpController,
            servoHttpController,
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

        // todo: vector, so that me-the-dumbass dont forget about changing the size
        std::array<Arduino::SetupAndLoopAware *, 9> setupAndLoopAwares = {
            &hardwareSerialSetup,
            &wiFi,
            &throttledLoopIndicator,
            &setupAndLoopAwareWebSerial,
            &otaUpdater,
            &mdns,
            &server,
            &throttledWiFiSignalStrengthLogger,
            &doorLock
        };
    };

}
