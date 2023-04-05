#pragma once

#include <array>
#include <cstdint>    // uint8_t, uint16_t
#include <functional> // std::reference_wrapper
#include <utility>    // std::move

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Esp.h>
#include <Servo.h>
#include <WebSerial.h>
#include <WString.h>

#include "DnApp/Arduino/HardwareSerialSetup.h"
#include "DnApp/Arduino/Hardware/Board.h"
#include "DnApp/Arduino/Hardware/DigitalPin.h"
#include "DnApp/Arduino/Hardware/LedBlinker.h"
#include "DnApp/Arduino/Kernel/LambdaSetupAndLoopAware.h"
#include "DnApp/Arduino/Kernel/MultipleSetupAndLoopAware.h"
#include "DnApp/Arduino/Kernel/ThrottledLoopAware.h"
#include "DnApp/Arduino/Kernel/SetupAndLoopAware.h"
#include "DnApp/Arduino/Logger/Endpoint/HardwareSerialLogger.h"
#include "DnApp/Arduino/Logger/Endpoint/WithArduinoStringLoggerToLogger.h"
#include "DnApp/Arduino/LoopIndicator.h"
#include "DnApp/Arduino/WelcomeMessagePrinter.h"
#include "DnApp/Esp/Esp8266/LogWiFiStrengthLoopAware.h"
#include "DnApp/Esp/Esp8266/MdnsSetupAndLoopAware.h"
#include "DnApp/Esp/Esp8266/WiFiSetupAndLoopAware.h"
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
#include "DnWiFiDoorLock/Arduino/DoorLock.h"
#include "DnWiFiDoorLock/Arduino/Furnace.h"
#include "DnWiFiDoorLock/Arduino/OTAUploaderSetupAndLoopAware.h"
#include "DnWiFiDoorLock/Arduino/Servo/Button.h"
#include "DnWiFiDoorLock/Arduino/Servo/Servo.h"

namespace DnWiFiDoorLock {
    class App final:
        public DnApp::Arduino::Kernel::SetupAndLoopAware {
    public:
        struct Config final {
            const char* const name;

            const char* const buildGitCommitHash;

            const unsigned long serialBitsPerSecond;

            const uint8_t servoPin;

            struct {
                const char* const ssid;

                const char* const password;
            } const wiFi;

            struct {
                const char* const hostname;

                const uint16_t port;
            } const webServer;

            struct {
                const char* const hostname;

                const uint16_t port;

                const char* const passwordMd5;
            } const otaUpload;

            struct {
                const uint8_t pressingAngle;

                const uint8_t notPressingAngle;

                const int pressingMilliseconds;
            } const furnaceHeaterButton;
        };

        explicit
        App(Config config):
            config{std::move(config)} {
        }

        auto onSetup() -> void override {
            getAppSetupAndLoopAwares().onSetup();
        }

        auto onLoop() -> void override {
            getAppSetupAndLoopAwares().onLoop();

            // todo: secure server
            // todo: handling door open/close with servo
        }
    private:
        static
        const auto MILLISECONDS_IN_SECOND = 1000;

        static
        const auto WIFI_STRENGTH_LOGGING_INTERVAL_MILLISECONDS = MILLISECONDS_IN_SECOND;

        static
        const auto LOOP_INDICATOR_LED_TOGGLE_INTERVAL_MILLISECONDS = MILLISECONDS_IN_SECOND;

        const Config config;

        auto& getBoard() {
            static auto service = DnApp::Arduino::Hardware::Board{};

            return service;
        }

        auto& getHardwareSerialLogger() {
            static auto service = DnApp::Arduino::Logger::Endpoint::HardwareSerialLogger{
                ::Serial
            };

            return service;
        }

        auto& getWebSerialLogger() {
            static auto service = DnApp::Esp::Logger::Endpoint::WebSerialLogger{
                ::WebSerial
            };

            return service;
        }

        auto& getLoggers() {
            static auto service = std::to_array<std::reference_wrapper<DnApp::Logger::Logger>>({
                getHardwareSerialLogger(),
                getWebSerialLogger()
            });

            return service;
        }

        auto& getMultipleLoggersLogger() {
            static auto service = DnApp::Logger::Decorator::SequenceLogger{
                getLoggers()
            };

            return service;
        }

        auto& getPrependLogLevelLogger() {
            static auto service = DnApp::Logger::Decorator::PrependLogLevelLogger{
                getMultipleLoggersLogger()
            };

            return service;
        }

        auto& getLogLevelThresholdFilteringLogger() {
            static auto service = DnApp::Logger::Decorator::LogLevelThresholdFilteringLogger{
                getPrependLogLevelLogger(),
                // lets not filter out anything by default
                DnApp::Logger::Logger::LOG_LEVEL::DEBUG
            };

            return service;
        }

        auto& getFreeHeapDecoratorLogger() {
            static auto service = DnApp::Esp::Logger::Decorator::MemoryDecoratorLogger{
                ::ESP,
                getLogLevelThresholdFilteringLogger()
            };

            return service;
        }

        auto& getLogger() {
            return getFreeHeapDecoratorLogger();
        }

        auto& getArduinoLogger() {
            static auto service = DnApp::Arduino::Logger::Endpoint::WithArduinoStringLoggerToLogger{
                getLogger()
            };

            return service;
        }

        auto& getArduinoServo() {
            static auto service = ::Servo{};

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
            static auto service = DnWiFiDoorLock::Arduino::Servo::Servo{
                getArduinoServo(),
                config.servoPin,
                600,
                2400,
                getArduinoLogger()
            };

            return service;
        }

        auto& getDoorLock() {
            static auto service = DnWiFiDoorLock::Arduino::DoorLock{
                getServo(),
                getLogger(),
                DnApp::Hardware::Servo::Angle::withDegrees(0).value(),
                DnApp::Hardware::Servo::Angle::withDegrees(180).value()
            };

            return service;
        }

        auto& getBuiltInLed() {
            // it is inverted for built–in led
            // https://github.com/nodemcu/nodemcu-devkit-v1.0/issues/16
            // https://stackoverflow.com/questions/46087828/why-is-nodemcu-triggering-gpio-in-reverse-when-using-lua
            static auto pin = DnApp::Arduino::Hardware::DigitalPin{DnApp::Arduino::Hardware::Board::BUILT_IN_LED_PIN};
            static auto led = DnApp::Hardware::LedOnDigitalPin{pin};
            static auto service = DnApp::Hardware::LedInverter{led};

            return service;
        }

        auto& getBuiltInLedBlinker() {
            static auto service = DnApp::Arduino::Hardware::LedBlinker{
                getBoard(),
                getBuiltInLed()
            };

            return service;
        }

        auto& getWiFi() {
            static auto service = DnApp::Esp::Esp8266::WiFiSetupAndLoopAware{
                // todo: figure out why `*ssid` crashes in `::WiFi.begin()` when using `PSTR("the ssid")`
                //       * https://discord.com/channels/583251190591258624/1063162264468865047/1063162264468865047
                //       * https://community.platformio.org/t/esp8266-why-is-pstr-crashing-on-text-in-a-function/31457/1
                //       * https://forum.arduino.cc/t/esp8266-why-is-pstr-crashing-on-text-in-a-function/1076744/1
                config.wiFi.ssid,
                config.wiFi.password,
                getBuiltInLedBlinker(),
                // WebSerial(Logger) cannot be injected, runtime crash for some reason
                // todo: find a way to inject full logger or at least add decorators
                getHardwareSerialLogger(),
                getBoard(),
                ::WiFi
            };

            return service;
        }

        auto& getMDNSSetupAndLoopAware() {
            static auto service = DnApp::Esp::Esp8266::MdnsSetupAndLoopAware{
                ::MDNS,
                getLogger(),
                config.webServer.hostname
            };

            return service;
        }

        auto& getOTAUploaderSetupAndLoopAware() {
            static auto service = DnWiFiDoorLock::Arduino::OTAUploaderSetupAndLoopAware{
                config.otaUpload.port,
                config.otaUpload.hostname,
                config.otaUpload.passwordMd5,
                getArduinoLogger()
            };

            return service;
        }

        auto& getWifiSignalStrengthLoggingLoopAware() {
            static auto filtered = DnApp::Logger::Decorator::LogLevelThresholdFilteringLogger{
                getLogger(),
                // switch to DEBUG when needed, to debug Wi-Fi issues
                DnApp::Logger::Logger::LOG_LEVEL::INFO
            };

            static auto logger = DnApp::Arduino::Logger::Endpoint::WithArduinoStringLoggerToLogger{
                filtered
            };

            static auto service = DnApp::Esp::Esp8266::LogWiFiStrengthLoopAware{
                ::WiFi,
                logger
            };

            return service;
        }

        auto& getThrottledWiFiSignalStrengthLoggingLoopAware() {
            static auto service = DnApp::Arduino::Kernel::ThrottledLoopAware{
                getWifiSignalStrengthLoggingLoopAware(),
                getBoard(),
                WIFI_STRENGTH_LOGGING_INTERVAL_MILLISECONDS
            };

            return service;
        }

        auto& getFurnaceHeaterButton() {
            static auto service = DnWiFiDoorLock::Arduino::Servo::Button{
                getBoard(),
                // todo: a different servo than DoorLock servo? ;p
                getServo(),
                DnApp::Hardware::Servo::Angle::withDegrees(config.furnaceHeaterButton.pressingAngle).value(),
                DnApp::Hardware::Servo::Angle::withDegrees(config.furnaceHeaterButton.notPressingAngle).value(),
                config.furnaceHeaterButton.pressingMilliseconds
            };

            return service;
        }

        auto& getFurnace() {
            static auto service = DnWiFiDoorLock::Arduino::Furnace{
                getFurnaceHeaterButton(),
                getLogger()
            };

            return service;
        }

        auto& getDoorLockHttpController() {
            static auto service = DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::DoorLockController{
                getBoard(),
                getDoorLock(),
                getLogger()
            };

            return service;
        }

        auto& getFurnaceHttpController() {
            static auto service = DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::FurnaceController{
                getBoard(),
                getFurnace(),
                getLogger()
            };

            return service;
        }

        // todo: in the end we don't need that, but it is useful for calibration
        auto& getServoHttpController() {
            static auto service = DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServoController{
                getServo(),
                getLogger(),
                config.name
            };

            return service;
        }

        auto& getEspServer() {
            static auto service = AsyncWebServer{
                config.webServer.port
            };

            return service;
        }

        auto& getServoButtonController() {
            static auto service = DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServoButtonController{
                config.name,
                getFurnaceHeaterButton(),
                getArduinoLogger()
            };

            return service;
        }

        auto& getServer() {
            static auto service = DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::Http::ServerSetup{
                ::WiFi,
                getEspServer(),
                config.webServer.hostname,
                config.webServer.port,
                getDoorLockHttpController(),
                getFurnaceHttpController(),
                getServoButtonController(),
                getServoHttpController(),
                getArduinoLogger()
            };

            return service;
        }

        auto& getHardwareSerialSetup() {
            static auto service = DnApp::Arduino::HardwareSerialSetup{
                Serial,
                getBoard(),
                config.serialBitsPerSecond
            };

            return service;
        }

        auto& getSetupAndLoopAwareWebSerial() {
            static auto service = DnWiFiDoorLock::Arduino::Esp8266::EspAsyncWebServer::WebSerial::Setup{
                ::WebSerial,
                getEspServer()
            };

            return service;
        }

        auto& getLoopIndicator() {
            static auto service = DnApp::Arduino::LoopIndicator{
                getBuiltInLed(),
                getBuiltInLedBlinker(),
                getArduinoLogger()
            };

            return service;
        }

        auto& getThrottledLoopIndicator() {
            static auto service = DnApp::Arduino::Kernel::ThrottledLoopAware{
                getLoopIndicator(),
                getBoard(),
                LOOP_INDICATOR_LED_TOGGLE_INTERVAL_MILLISECONDS
            };

            return service;
        }

        auto& getSetupStartIndicator() {
            // todo: better init
            //      a.) improve/new template to handle named constructors
            //      b.) improve LambdaSetupAndLoopAware to get rid of named constructor
            //          https://boost-ext.github.io/di/tutorial.html – grep "struct width {"
            static auto service = DnApp::Arduino::Kernel::LambdaSetupAndLoopAware::createSetupAware([&] () {
                getBuiltInLedBlinker().blinkFast(5);
            });

            return service;
        }

        auto& getHardwareSerialWelcomeMessageSetup() const {
            static auto service = DnApp::Arduino::WelcomeMessagePrinter{
                ::Serial,
                config.name,
                {.gitCommitHash = config.buildGitCommitHash}
            };

            return service;
        }

        auto& getSetupAndLoopAwares() {
            static auto service = std::to_array<
                DnApp::Arduino::Kernel::SetupAndLoopAwareReference
            >({
                getSetupStartIndicator(),
                getHardwareSerialSetup(),
                getHardwareSerialWelcomeMessageSetup(),
                getWiFi(),
                getThrottledLoopIndicator(),
                getSetupAndLoopAwareWebSerial(),
                getOTAUploaderSetupAndLoopAware(),
                getMDNSSetupAndLoopAware(),
                getServer(),
                getThrottledWiFiSignalStrengthLoggingLoopAware(),
                getDoorLock(),
                getFurnaceHeaterButton()
            });

            return service;
        }

        // cannot have `auto` return type, as order of methods declaration matters then
        DnApp::Arduino::Kernel::MultipleSetupAndLoopAware& getAppSetupAndLoopAwares() {
            static auto service = DnApp::Arduino::Kernel::MultipleSetupAndLoopAware{
                getSetupAndLoopAwares()
            };

            return service;
        }
    };
}
