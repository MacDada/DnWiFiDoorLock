#pragma once

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
#include "DnWiFiDoorLock/Arduino/LambdaSetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/Led.h"
#include "DnWiFiDoorLock/Arduino/Logger/HardwareSerialLogger.h"
#include "DnWiFiDoorLock/Arduino/Logger/MultipleLoggersLogger.h"
#include "DnWiFiDoorLock/Arduino/LoopIndicator.h"
#include "DnWiFiDoorLock/Arduino/MultipleSetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/OTAUpdater.h"
#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/ThrottledLoopAware.h"

namespace DnWiFiDoorLock {

    class App final: public Arduino::SetupAndLoopAware {
    public:
        void onSetup() override;

        void onLoop() override;

    private:
        static const int MILLISECONDS_IN_SECOND = 1000;

        static const int WIFI_STRENGTH_LOGGING_INTERVAL_MILLISECONDS = MILLISECONDS_IN_SECOND;

        static const int LOOP_INDICATOR_LED_TOGGLE_INTERVAL_MILLISECONDS = MILLISECONDS_IN_SECOND;

        template<typename T>
        T &shared() {
            static T service{};

            return service;
        }

        template<typename T, typename ...Args>
        T &shared(Args &&... args) {
            static T service{std::forward<Args>(args)...};

            return service;
        }

        auto &getHardware() {
            return shared<const DnWiFiDoorLock::Arduino::Hardware>();
        }

        auto &getHardwareSerialLogger() {
            return shared<DnWiFiDoorLock::Arduino::Logger::HardwareSerialLogger>(
                Serial
            );
        }

        auto &getWebSerialLogger() {
            return shared<DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial::Logger>(
                WebSerial
            );
        }

        auto &getLoggers() {
            return shared<std::vector<DnWiFiDoorLock::Arduino::Logger::LoggerReference>>(
                getHardwareSerialLogger(),
                getWebSerialLogger()
            );
        }

        auto &getLogger() {
            return shared<DnWiFiDoorLock::Arduino::Logger::MultipleLoggersLogger>(
                getLoggers()
            );
        }

        auto &getArduinoServo() {
            return shared<::Servo>();
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
        auto &getServo() {
            return shared<DnWiFiDoorLock::Arduino::Servo::Servo>(
                getArduinoServo(),
                (byte) SERVO_PIN,
                600,
                2400,
                getLogger()
            );
        }

        auto &getDoorLock() {
            return shared<DnWiFiDoorLock::Arduino::DoorLock>(
                getServo(),
                getLogger(),
                // todo: CLion bug report
                //       https://discord.com/channels/583251190591258624/742849025191051326/1005110176363319436
                //       https://discord.com/channels/583251190591258624/742849025191051326/1005133740370055229
                (byte) 0,
                (byte) 180
            );
        }

        auto &getBuiltInLed() {
            return shared<const DnWiFiDoorLock::Arduino::Led>(
                getHardware(),
                DnWiFiDoorLock::Arduino::Hardware::BUILT_IN_LED_PIN
            );
        }

        auto &getWiFi() {
            return shared<DnWiFiDoorLock::Arduino::Esp82666::WiFi::WiFi>(
                WIFI_SSID,
                WIFI_PASSWORD,
                getBuiltInLed(),
                // WebSerial(Logger) cannot be injected, runtime crash for some reason
                getHardwareSerialLogger(),
                getHardware(),
                ::WiFi
            );
        }

        auto &getMdns() {
            return shared<DnWiFiDoorLock::Arduino::Esp8266::MDNSSetupAndLoopAware>(
                MDNS,
                getLogger(),
                WEB_SERVER_HOST_NAME
            );
        }

        auto &getOtaUpdater() {
            return shared<DnWiFiDoorLock::Arduino::OTAUpdater>(
                OTA_UPDATE_PORT,
                OTA_UPDATE_HOST,
                OTA_UPDATE_PASSWORD_MD5,
                getLogger()
            );
        }

        auto &getWifiSignalStrengthLogger() {
             return shared<DnWiFiDoorLock::Arduino::Esp8266::WiFi::LoopAwareSignalStrengthLogger>(
                 ::WiFi,
                 getLogger()
             );
        }

        auto &getThrottledWiFiSignalStrengthLogger() {
            return shared<DnWiFiDoorLock::Arduino::ThrottledLoopAware>(
                getWifiSignalStrengthLogger(),
                getHardware(),
                WIFI_STRENGTH_LOGGING_INTERVAL_MILLISECONDS
            );
        }

        auto &getDoorLockHttpController() {
            return shared<DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::DoorLockController>(
                getHardware(),
                getDoorLock(),
                getLogger()
            );
        }

        // todo: in the end we don't need that, but it is useful for calibration
        auto &getServoHttpController() {
            return shared<DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServoController>(
                getServo(),
                getLogger()
            );
        }

        auto &getEspServer() {
            return shared<AsyncWebServer>(
                (byte) WEB_SERVER_PORT
            );
        }

        auto &getServer() {
            return shared<DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServerSetup>(
                getEspServer(),
                WEB_SERVER_HOST_NAME,
                (byte) WEB_SERVER_PORT,
                getDoorLockHttpController(),
                getServoHttpController(),
                getLogger()
            );
        }

        auto &getHardwareSerialSetup() {
            return shared<DnWiFiDoorLock::Arduino::HardwareSerialSetup>(
                Serial,
                getHardware(),
                SERIAL_BITS_PER_SECOND
            );
        }

        auto &getSetupAndLoopAwareWebSerial() {
            return shared<DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial::Setup>(
                WebSerial,
                getEspServer()
            );
        }

        auto &getLoopIndicator() {
            return shared<DnWiFiDoorLock::Arduino::LoopIndicator>(
                getBuiltInLed(),
                getLogger()
            );
        }

        auto &getThrottledLoopIndicator() {
            return shared<DnWiFiDoorLock::Arduino::ThrottledLoopAware>(
                getLoopIndicator(),
                getHardware(),
                LOOP_INDICATOR_LED_TOGGLE_INTERVAL_MILLISECONDS
            );
        }

        auto &getSetupStartIndicator() {
            // todo: better init
            //      a.) improve/new template to handle named constructors
            //      b.) improve LambdaSetupAndLoopAware to get rid of named constructor
            //          https://boost-ext.github.io/di/tutorial.html – grep "struct width {"
            static auto service = DnWiFiDoorLock::Arduino::LambdaSetupAndLoopAware::createSetupAware([&]() {
                getBuiltInLed().blinkFast(5);
            });

            return service;
        }

        auto &getSetupAndLoopAwares() {
            return shared<std::vector<DnWiFiDoorLock::Arduino::SetupAndLoopAwareReference>>(
                getSetupStartIndicator(),
                getHardwareSerialSetup(),
                getWiFi(),
                getThrottledLoopIndicator(),
                getSetupAndLoopAwareWebSerial(),
                getOtaUpdater(),
                getMdns(),
                getServer(),
                getThrottledWiFiSignalStrengthLogger(),
                getDoorLock()
            );
        }

        auto &getAppSetupAndLoopAwares() {
            return shared<DnWiFiDoorLock::Arduino::MultipleSetupAndLoopAware>(
                getSetupAndLoopAwares()
            );
        }
    };

}
