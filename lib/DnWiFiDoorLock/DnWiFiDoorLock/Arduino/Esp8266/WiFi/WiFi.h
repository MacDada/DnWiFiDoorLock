#pragma once

#include <type_traits>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WString.h>

#include "DnApp/Arduino/Logger/Logger.h"
#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/LedBlinker.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Esp82666::WiFi {
    class WiFi final: public DnWiFiDoorLock::Arduino::SetupAndLoopAware {
    public:
        WiFi(
            const char *ssid,
            const char *password,
            DnWiFiDoorLock::Arduino::LedBlinker &ledBlinker,
            DnApp::Arduino::Logger::Logger &logger,
            const DnWiFiDoorLock::Arduino::Hardware &hardware,
            ESP8266WiFiClass &esp8266WiFi
        );

        void onSetup() override;

        void onLoop() override;
    private:
        const char *const ssid;

        const char *const password;

        DnWiFiDoorLock::Arduino::LedBlinker &ledBlinker;

        DnApp::Arduino::Logger::Logger &logger;

        const DnWiFiDoorLock::Arduino::Hardware &hardware;

        ESP8266WiFiClass &esp8266WiFi;

        void connect();

        void waitForConnection();

        const char *wiFiConnectionStatusToString(uint8_t status) const;

        void informAboutConnectingIssue(int tries, int status);
    };

    static_assert(!std::is_abstract<WiFi>());
}
