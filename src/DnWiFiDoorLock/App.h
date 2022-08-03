#pragma once

#include <array>
#include <vector>

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>
#include <WebSerial.h>

#include "config.h"

#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/DoorLockController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/ServerSetup.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/ServoController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/WebSerial/Setup.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/WebSerial/Logger.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/MDNSSetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/WiFi/LoopAwareSignalStrengthLogger.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/WiFi/WiFi.h"
#include "DnWiFiDoorLock/Arduino/DoorLock.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/HardwareSerialSetup.h"
#include "DnWiFiDoorLock/Arduino/Led.h"
#include "DnWiFiDoorLock/Arduino/Logger/HardwareSerialLogger.h"
#include "DnWiFiDoorLock/Arduino/Logger/MultipleLoggersLogger.h"
#include "DnWiFiDoorLock/Arduino/LoopIndicator.h"
#include "DnWiFiDoorLock/Arduino/OTAUpdater.h"
#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/ThrottledLoopAware.h"

namespace DnWiFiDoorLock {

    class App final: public Arduino::SetupAndLoopAware {
        using DoorLock                      = DnWiFiDoorLock::Arduino::DoorLock;
        using DoorLockController            = DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::DoorLockController;
        using HardwareSerialLogger          = DnWiFiDoorLock::Arduino::Logger::HardwareSerialLogger;
        using Led                           = DnWiFiDoorLock::Arduino::Led;
        using LoopAwareSignalStrengthLogger = DnWiFiDoorLock::Arduino::Esp8266::WiFi::LoopAwareSignalStrengthLogger;
        using MultipleLoggersLogger         = DnWiFiDoorLock::Arduino::Logger::MultipleLoggersLogger;
        using ServerSetup                   = DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServerSetup;
        using ServoController               = DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServoController;
        using WebSerialLogger               = DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial::Logger;
        using WebSerialSetup                = DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial::Setup;

    public:
        void onSetup() override;

        void onLoop() override;

    private:
        static const int MILLISECONDS_IN_SECOND = 1000;

        static const int WIFI_STRENGTH_LOGGING_INTERVAL_MILLISECONDS = MILLISECONDS_IN_SECOND;

        static const int LOOP_INDICATOR_LED_TOGGLE_INTERVAL_MILLISECONDS = MILLISECONDS_IN_SECOND;

        DnWiFiDoorLock::Arduino::Hardware hardware;

        HardwareSerialLogger hardwareSerialLogger{Serial};

        WebSerialLogger webSerialLogger{WebSerial};

        // todo: smart pointers?
        //       https://discord.com/channels/583251190591258624/583254410218700800/1004433192889102336
        std::vector<DnWiFiDoorLock::Arduino::Logger::Logger *> loggers = {
            &hardwareSerialLogger,
            &webSerialLogger
        };

        MultipleLoggersLogger logger{loggers};

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
        Arduino::Servo::Servo servo{arduinoServo, SERVO_PIN, 600, 2400, logger};

        DoorLock doorLock{servo, logger, 0, 180};

        Led builtInLed{hardware, DnWiFiDoorLock::Arduino::Hardware::BUILT_IN_LED_PIN};

        DnWiFiDoorLock::Arduino::Esp82666::WiFi::WiFi wiFi{
            WIFI_SSID,
            WIFI_PASSWORD,
            builtInLed,
            // WebSerial(Logger) cannot be injected, runtime crash for some reason
            hardwareSerialLogger,
            hardware,
            ::WiFi
        };

        Arduino::Esp8266::MDNSSetupAndLoopAware mdns{
            MDNS,
            logger,
            WEB_SERVER_HOST_NAME
        };

        DnWiFiDoorLock::Arduino::OTAUpdater otaUpdater{
            OTA_UPDATE_PORT,
            OTA_UPDATE_HOST,
            OTA_UPDATE_PASSWORD_MD5,
            logger
        };

        LoopAwareSignalStrengthLogger wifiSignalStrengthLogger{
            ::WiFi,
            logger
        };

        Arduino::ThrottledLoopAware throttledWiFiSignalStrengthLogger{
            wifiSignalStrengthLogger,
            hardware,
            WIFI_STRENGTH_LOGGING_INTERVAL_MILLISECONDS
        };

        DoorLockController doorLockHttpController{hardware, doorLock, logger};

        // todo: in the end we don't need that, but it is useful for calibration
        ServoController servoHttpController{servo, logger};

        AsyncWebServer espServer{WEB_SERVER_PORT};

        ServerSetup server{
            espServer,
            WEB_SERVER_HOST_NAME,
            WEB_SERVER_PORT,
            doorLockHttpController,
            servoHttpController,
            logger
        };

        Arduino::HardwareSerialSetup hardwareSerialSetup{
            Serial,
            hardware,
            SERIAL_BITS_PER_SECOND
        };

        WebSerialSetup setupAndLoopAwareWebSerial{WebSerial, espServer};

        Arduino::LoopIndicator loopIndicator{builtInLed, logger};

        Arduino::ThrottledLoopAware throttledLoopIndicator{
            loopIndicator,
            hardware,
            LOOP_INDICATOR_LED_TOGGLE_INTERVAL_MILLISECONDS
        };

        // todo: vector, so that me-the-dumbass dont forget about changing the size
        std::array<Arduino::SetupAndLoopAware *const, 9> setupAndLoopAwares = {
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
