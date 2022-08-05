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

        const DnWiFiDoorLock::Arduino::Hardware &getHardware() {
            static const DnWiFiDoorLock::Arduino::Hardware service{};

            return service;
        }

        HardwareSerialLogger &getHardwareSerialLogger() {
            static HardwareSerialLogger service{Serial};

            return service;
        }

        WebSerialLogger &getWebSerialLogger() {
            static WebSerialLogger service{WebSerial};

            return service;
        }

        std::vector<DnWiFiDoorLock::Arduino::Logger::LoggerReference> &getLoggers() {
            static std::vector<DnWiFiDoorLock::Arduino::Logger::LoggerReference> service{
                getHardwareSerialLogger(),
                getWebSerialLogger()
            };

            return service;
        }

        DnWiFiDoorLock::Arduino::Logger::Logger &getLogger() {
            static MultipleLoggersLogger service{
                getLoggers()
            };

            return service;
        }

        ::Servo &getArduinoServo() {
            static ::Servo service;

            return service;
        }

        // todo: why the servo does not reach proper 0-180 degree angles by default?
        //      * https://www.arduino.cc/reference/en/libraries/servo/attach/
        //          - the docs say the default pulse should be 544-2400
        //      * the lib actually defaults to 1000-2000 [which sounds like the "industry standard"]
        //          - note when testing: changing the max does not impact the min and vice versa
        //      * the servo's specs: https://download.kamami.pl/p195301-HD-1501MG.pdf
        //          - according to the specs i dont know what to think, but i guess it should be 800-2200?
        //      * verified values that work OK: 500-2500
        //      * setting a smaller range just to be safe
        Arduino::Servo::Servo &getServo() {
            static Arduino::Servo::Servo service{getArduinoServo(), SERVO_PIN, 600, 2400, getLogger()};

            return service;
        }

        DoorLock &getDoorLock() {
            static DoorLock service{getServo(), getLogger(), 0, 180};

            return service;
        }

        const Led &getBuiltInLed() {
            static const Led service{getHardware(), DnWiFiDoorLock::Arduino::Hardware::BUILT_IN_LED_PIN};

            return service;
        }

        DnWiFiDoorLock::Arduino::Esp82666::WiFi::WiFi &getWiFi() {
            static DnWiFiDoorLock::Arduino::Esp82666::WiFi::WiFi service{
                WIFI_SSID,
                WIFI_PASSWORD,
                getBuiltInLed(),
                // WebSerial(Logger) cannot be injected, runtime crash for some reason
                getHardwareSerialLogger(),
                getHardware(),
                ::WiFi
            };

            return service;
        }

        Arduino::Esp8266::MDNSSetupAndLoopAware &getMdns() {
            static Arduino::Esp8266::MDNSSetupAndLoopAware service{
                MDNS,
                getLogger(),
                WEB_SERVER_HOST_NAME
            };

            return service;
        }

        DnWiFiDoorLock::Arduino::OTAUpdater &getOtaUpdater() {
            static DnWiFiDoorLock::Arduino::OTAUpdater service{
                OTA_UPDATE_PORT,
                OTA_UPDATE_HOST,
                OTA_UPDATE_PASSWORD_MD5,
                getLogger()
            };

            return service;
        }

        LoopAwareSignalStrengthLogger &getWifiSignalStrengthLogger() {
             static LoopAwareSignalStrengthLogger service{
                 ::WiFi,
                getLogger()
             };

             return service;
        }

        Arduino::ThrottledLoopAware &getThrottledWiFiSignalStrengthLogger() {
            static Arduino::ThrottledLoopAware service{
                getWifiSignalStrengthLogger(),
                getHardware(),
                WIFI_STRENGTH_LOGGING_INTERVAL_MILLISECONDS
            };

            return service;
        }

        DoorLockController &getDoorLockHttpController() {
            static DoorLockController service{getHardware(), getDoorLock(), getLogger()};

            return service;
        }

        // todo: in the end we don't need that, but it is useful for calibration
        ServoController &getServoHttpController() {
            static ServoController service{getServo(), getLogger()};

            return service;
        }

        AsyncWebServer &getEspServer() {
            static AsyncWebServer service{WEB_SERVER_PORT};

            return service;
        }

        ServerSetup &getServer() {
            static ServerSetup service{
                getEspServer(),
                WEB_SERVER_HOST_NAME,
                WEB_SERVER_PORT,
                getDoorLockHttpController(),
                getServoHttpController(),
                getLogger()
            };

            return service;
        }

        Arduino::HardwareSerialSetup &getHardwareSerialSetup() {
            static Arduino::HardwareSerialSetup service{
                Serial,
                getHardware(),
                SERIAL_BITS_PER_SECOND
            };

            return service;
        }

        WebSerialSetup &getSetupAndLoopAwareWebSerial() {
            static WebSerialSetup service{WebSerial, getEspServer()};

            return service;
        }

        Arduino::LoopIndicator &getLoopIndicator() {
            static Arduino::LoopIndicator service{getBuiltInLed(), getLogger()};

            return service;
        }

        Arduino::ThrottledLoopAware &getThrottledLoopIndicator() {
            static Arduino::ThrottledLoopAware service{
                getLoopIndicator(),
                getHardware(),
                LOOP_INDICATOR_LED_TOGGLE_INTERVAL_MILLISECONDS
            };

            return service;
        }

        // todo: vector, so that me-the-dumbass dont forget about changing the size
        std::array<Arduino::SetupAndLoopAwareReference, 9> &getSetupAndLoopAwares() {
            static std::array<Arduino::SetupAndLoopAwareReference, 9> service{
                getHardwareSerialSetup(),
                getWiFi(),
                getThrottledLoopIndicator(),
                getSetupAndLoopAwareWebSerial(),
                getOtaUpdater(),
                getMdns(),
                getServer(),
                getThrottledWiFiSignalStrengthLogger(),
                getDoorLock()
            };

            return service;
        }
    };

}
