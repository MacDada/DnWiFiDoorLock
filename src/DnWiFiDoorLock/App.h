#pragma once

#include <array>
#include <vector>

// todo: ordering
#include <Arduino.h>
#include <Servo.h>
#include <WebSerial.h>

#include "Arduino/Esp8266/EspAsyncWebServer/Http/DoorLockController.h"
#include "Arduino/Esp8266/EspAsyncWebServer/Http/ServoController.h"
#include "Arduino/Esp8266/EspAsyncWebServer/WebSerial/SetupAndLoopAwareWebSerial.h"
#include "Arduino/Esp8266/WiFi/LoopAwareSignalStrengthLogger.h"
#include "Arduino/HardwareSerialSetup.h"
#include "Arduino/LoopIndicator.h"
#include "Arduino/Servo/Servo.h"
#include "Arduino/SetupAndLoopAware.h"
#include "Arduino/ThrottledLoopAware.h"
#include "config.h"
#include "OTAUpdater.h"
#include "ESPAsyncWebServer.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/DoorLock.h"
#include "Led.h"
#include "WiFi.h"
#include "HttpServer.h"
#include "Logger/HardwareSerialArduinoLogger.h"
#include "Logger/WebSerialArduinoLogger.h"
#include "Logger/MultipleLoggersArduinoLogger.h"

namespace DnWiFiDoorLock {

// todo: indentation
using DnWiFiDoorLock::Arduino::DoorLock;
using DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::DoorLockController;
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

        DoorLock doorLock = DoorLock(servo, logger, 0, 180);

        Led builtInLed = Led(hardware, DnWiFiDoorLock::Arduino::Hardware::BUILT_IN_LED_PIN);

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

        DoorLockController doorLockHttpController = DoorLockController(hardware, doorLock);

        // todo: in the end we don't need that, but it is useful for calibration
        ServoController servoHttpController = ServoController(servo, logger);

        AsyncWebServer espServer = AsyncWebServer(WEB_SERVER_PORT);

        HttpServer server = HttpServer(
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
        std::array<Arduino::SetupAndLoopAware *, 8> setupAndLoopAwares = {
            &hardwareSerialSetup,
            &wiFi,
            &throttledLoopIndicator,
            &setupAndLoopAwareWebSerial,
            &otaUpdater,
            &server,
            &throttledWiFiSignalStrengthLogger,
            &doorLock
        };
    };

}
