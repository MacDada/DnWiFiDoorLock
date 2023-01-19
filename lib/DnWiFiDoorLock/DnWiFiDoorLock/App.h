#pragma once

#include <functional>
#include <vector>

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Esp.h>
#include <Servo.h>
#include <WebSerial.h>
#include <WString.h>

#include "DnApp/Arduino/Hardware/DigitalPin.h"
#include "DnApp/Arduino/Logger/Endpoint/HardwareSerialLogger.h"
#include "DnApp/Arduino/Logger/Endpoint/WithArduinoStringLoggerToLogger.h"
#include "DnApp/Esp/Logger/Decorator/MemoryDecoratorLogger.h"
#include "DnApp/Esp/Logger/Endpoint/WebSerialLogger.h"
#include "DnApp/Hardware/LedInverter.h"
#include "DnApp/Hardware/LedOnDigitalPin.h"
#include "DnApp/Logger/Decorator/LogLevelThresholdFilteringLogger.h"
#include "DnApp/Logger/Decorator/PrependLogLevelLogger.h"
#include "DnApp/Logger/Decorator/SequenceLogger.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/DoorLockController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/FurnaceController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/ServerSetup.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/ServoButtonController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/Http/ServoController.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/EspAsyncWebServer/WebSerial/Setup.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/MDNSSetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/WiFi/LoopAwareSignalStrengthLogger.h"
#include "DnWiFiDoorLock/Arduino/Esp8266/WiFi/WiFi.h"
#include "DnWiFiDoorLock/Arduino/DoorLock.h"
#include "DnWiFiDoorLock/Arduino/Furnace.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/HardwareSerialSetup.h"
#include "DnWiFiDoorLock/Arduino/LambdaSetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/LedBlinker.h"
#include "DnWiFiDoorLock/Arduino/LoopIndicator.h"
#include "DnWiFiDoorLock/Arduino/MultipleSetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/OTAUpdater.h"
#include "DnWiFiDoorLock/Arduino/Servo/Button.h"
#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/ThrottledLoopAware.h"

namespace DnWiFiDoorLock {
    class App final:
        public Arduino::SetupAndLoopAware {
    private:
        static const int MILLISECONDS_IN_SECOND = 1000;

        static const int WIFI_STRENGTH_LOGGING_INTERVAL_MILLISECONDS = MILLISECONDS_IN_SECOND;

        static const int LOOP_INDICATOR_LED_TOGGLE_INTERVAL_MILLISECONDS = MILLISECONDS_IN_SECOND;

        auto& getHardware() {
            static const DnWiFiDoorLock::Arduino::Hardware service{};

            return service;
        }

        auto& getHardwareSerialLogger() {
            static DnApp::Arduino::Logger::Endpoint::HardwareSerialLogger service{
                ::Serial
            };

            return service;
        }

        auto& getWebSerialLogger() {
            static DnApp::Esp::Logger::Endpoint::WebSerialLogger service{
                ::WebSerial
            };

            return service;
        }

        auto& getLoggers() {
            static std::vector<std::reference_wrapper<DnApp::Logger::Logger>> service{
                getHardwareSerialLogger(),
                getWebSerialLogger()
            };

            return service;
        }

        auto& getMultipleLoggersLogger() {
            static DnApp::Logger::Decorator::SequenceLogger service{
                getLoggers()
            };

            return service;
        }

        auto& getPrependLogLevelLogger() {
            static DnApp::Logger::Decorator::PrependLogLevelLogger service{
                getMultipleLoggersLogger()
            };

            return service;
        }

        auto& getFreeHeapDecoratorLogger() {
            static DnApp::Esp::Logger::Decorator::MemoryDecoratorLogger service{
                ::ESP,
                getPrependLogLevelLogger()
            };

            return service;
        }

        auto& getLogger() {
            static DnApp::Logger::Decorator::LogLevelThresholdFilteringLogger service{
                getFreeHeapDecoratorLogger(),
                // lets not filter out anything by default
                DnApp::Logger::Logger::LOG_LEVEL::DEBUG
            };

            return service;
        }

        auto& getArduinoLogger() {
            static auto service = DnApp::Arduino::Logger::Endpoint::WithArduinoStringLoggerToLogger{
                getLogger()
            };

            return service;
        }

        auto& getArduinoServo() {
            static ::Servo service{};

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
        auto& getServo() {
            static DnWiFiDoorLock::Arduino::Servo::Servo service{
                getArduinoServo(),
                (byte) SERVO_PIN,
                600,
                2400,
                getArduinoLogger()
            };

            return service;
        }

        auto& getDoorLock() {
            static DnWiFiDoorLock::Arduino::DoorLock service{
                getServo(),
                getLogger(),
                // todo: CLion bug report
                //       https://discord.com/channels/583251190591258624/742849025191051326/1005110176363319436
                //       https://discord.com/channels/583251190591258624/742849025191051326/1005133740370055229
                (byte) 0,
                (byte) 180
            };

            return service;
        }

        auto& getBuiltInLed() {
            // it is inverted for built–in led
            // https://github.com/nodemcu/nodemcu-devkit-v1.0/issues/16
            // https://stackoverflow.com/questions/46087828/why-is-nodemcu-triggering-gpio-in-reverse-when-using-lua
            static DnApp::Arduino::Hardware::DigitalPin pin{DnWiFiDoorLock::Arduino::Hardware::BUILT_IN_LED_PIN};
            static DnApp::Hardware::LedOnDigitalPin led{pin};
            static DnApp::Hardware::LedInverter service{led};

            return service;
        }

        auto& getBuiltInLedBlinker() {
            static auto service = DnWiFiDoorLock::Arduino::LedBlinker{
                getHardware(),
                getBuiltInLed()
            };

            return service;
        }

        auto& getWiFi() {
            static DnWiFiDoorLock::Arduino::Esp82666::WiFi::WiFi service{
                // todo: figure out why `*ssid` crashes in `::WiFi.begin()` when using `PSTR(WIFI_SSID)`
                //       * https://discord.com/channels/583251190591258624/1063162264468865047/1063162264468865047
                //       * https://community.platformio.org/t/esp8266-why-is-pstr-crashing-on-text-in-a-function/31457/1
                //       * https://forum.arduino.cc/t/esp8266-why-is-pstr-crashing-on-text-in-a-function/1076744/1
                WIFI_SSID,
                PSTR(WIFI_PASSWORD),
                getBuiltInLedBlinker(),
                // WebSerial(Logger) cannot be injected, runtime crash for some reason
                getHardwareSerialLogger(),
                getHardware(),
                ::WiFi
            };

            return service;
        }

        auto& getMdns() {
            static DnWiFiDoorLock::Arduino::Esp8266::MDNSSetupAndLoopAware service{
                MDNS,
                getLogger(),
                PSTR(WEB_SERVER_HOST_NAME)
            };

            return service;
        }

        auto& getOtaUpdater() {
            static DnWiFiDoorLock::Arduino::OTAUpdater service{
                OTA_UPDATE_PORT,
                PSTR(OTA_UPDATE_HOST),
                PSTR(OTA_UPDATE_PASSWORD_MD5),
                getArduinoLogger()
            };

            return service;
        }

        auto& getWifiSignalStrengthLoggingLoopAware() {
            static DnApp::Logger::Decorator::LogLevelThresholdFilteringLogger filtered{
                getLogger(),
                // switch to DEBUG when needed, to debug Wi-Fi issues
                DnApp::Logger::Logger::LOG_LEVEL::INFO
            };

            static DnApp::Arduino::Logger::Endpoint::WithArduinoStringLoggerToLogger logger{
                filtered
            };

            static DnWiFiDoorLock::Arduino::Esp8266::WiFi::LoopAwareSignalStrengthLogger service{
                ::WiFi,
                logger
            };

            return service;
        }

        auto& getThrottledWiFiSignalStrengthLogger() {
            static DnWiFiDoorLock::Arduino::ThrottledLoopAware service{
                getWifiSignalStrengthLoggingLoopAware(),
                getHardware(),
                WIFI_STRENGTH_LOGGING_INTERVAL_MILLISECONDS
            };

            return service;
        }

        auto& getFurnaceHeaterButton() {
            static DnWiFiDoorLock::Arduino::Servo::Button service{
                getHardware(),
                // todo: a different servo than DoorLock servo? ;p
                getServo(),
                FURNACE_HEATER_BUTTON_PRESSING_ANGLE,
                FURNACE_HEATER_BUTTON_NOT_PRESSING_ANGLE,
                FURNACE_HEATER_BUTTON_PRESSING_MILLISECONDS
            };

            return service;
        }

        auto& getFurnace() {
            static DnWiFiDoorLock::Arduino::Furnace service{
                getFurnaceHeaterButton(),
                getLogger()
            };

            return service;
        }

        auto& getDoorLockHttpController() {
            static DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::DoorLockController service{
                getHardware(),
                getDoorLock(),
                getLogger()
            };

            return service;
        }

        auto& getFurnaceHttpController() {
            static DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::FurnaceController service{
                getHardware(),
                getFurnace(),
                getLogger()
            };

            return service;
        }

        // todo: in the end we don't need that, but it is useful for calibration
        auto& getServoHttpController() {
            static DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServoController service{
                getServo(),
                getLogger(),
                PSTR(APP_NAME)
            };

            return service;
        }

        auto& getEspServer() {
            static AsyncWebServer service{
                (byte) WEB_SERVER_PORT
            };

            return service;
        }

        auto& getServoButtonController() {
            static DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServoButtonController service{
                PSTR(APP_NAME),
                getFurnaceHeaterButton(),
                getArduinoLogger()
            };

            return service;
        }

        auto& getServer() {
            static DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServerSetup service{
                ::WiFi,
                getEspServer(),
                PSTR(WEB_SERVER_HOST_NAME),
                (byte) WEB_SERVER_PORT,
                getDoorLockHttpController(),
                getFurnaceHttpController(),
                getServoButtonController(),
                getServoHttpController(),
                getArduinoLogger()
            };

            return service;
        }

        auto& getHardwareSerialSetup() {
            static DnWiFiDoorLock::Arduino::HardwareSerialSetup service{
                Serial,
                getHardware(),
                SERIAL_BITS_PER_SECOND,
                PSTR(APP_NAME)
            };

            return service;
        }

        auto& getSetupAndLoopAwareWebSerial() {
            static DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial::Setup service{
                WebSerial,
                getEspServer()
            };

            return service;
        }

        auto& getLoopIndicator() {
            static DnWiFiDoorLock::Arduino::LoopIndicator service{
                getBuiltInLed(),
                getBuiltInLedBlinker(),
                getArduinoLogger()
            };

            return service;
        }

        auto& getThrottledLoopIndicator() {
            static DnWiFiDoorLock::Arduino::ThrottledLoopAware service{
                getLoopIndicator(),
                getHardware(),
                LOOP_INDICATOR_LED_TOGGLE_INTERVAL_MILLISECONDS
            };

            return service;
        }

        auto& getSetupStartIndicator() {
            // todo: better init
            //      a.) improve/new template to handle named constructors
            //      b.) improve LambdaSetupAndLoopAware to get rid of named constructor
            //          https://boost-ext.github.io/di/tutorial.html – grep "struct width {"
            static auto service = DnWiFiDoorLock::Arduino::LambdaSetupAndLoopAware::createSetupAware([&]() {
                getBuiltInLedBlinker().blinkFast(5);
            });

            return service;
        }

        auto& getSetupAndLoopAwares() {
            static std::vector<DnWiFiDoorLock::Arduino::SetupAndLoopAwareReference> service{
                getSetupStartIndicator(),
                getHardwareSerialSetup(),
                getWiFi(),
                getThrottledLoopIndicator(),
                getSetupAndLoopAwareWebSerial(),
                getOtaUpdater(),
                getMdns(),
                getServer(),
                getThrottledWiFiSignalStrengthLogger(),
                getDoorLock(),
                getFurnaceHeaterButton()
            };

            return service;
        }

        auto& getAppSetupAndLoopAwares() {
            static DnWiFiDoorLock::Arduino::MultipleSetupAndLoopAware service{
                getSetupAndLoopAwares()
            };

            return service;
        }
    // todo: why it cannot be on top of the file? complaining about `auto` ;p
    public:
        void onSetup() override {
            getAppSetupAndLoopAwares().onSetup();
        }

        void onLoop() override {
            getAppSetupAndLoopAwares().onLoop();

            // todo: secure server
            // todo: handling door open/close with servo
        }
    };
}
