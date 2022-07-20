#pragma once

#include <type_traits>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "Arduino/SetupAndLoopAware.h"
#include "Hardware.h"
#include "Led.h"
#include "Logger/ArduinoLogger.h"

namespace DnWiFiDoorLock {

    class WiFi final: public Arduino::SetupAndLoopAware {
    public:
        WiFi(
            const char *ssid,
            const char *password,
            Led &led,
            Logger::ArduinoLogger &logger,
            Hardware &hardware,
            ESP8266WiFiClass &esp8266WiFi
        );

        void onSetup() override;

        void onLoop() override;

    private:
        const char *ssid;

        const char *password;

        Led &led;

        Logger::ArduinoLogger &logger;

        Hardware &hardware;

        ESP8266WiFiClass &esp8266WiFi;

        void connect();

        void waitForConnection();

        const char *wiFiConnectionStatusToString(uint8_t status);

        void informAboutConnectingIssue(int tries, int status);
    };

    static_assert(!std::is_abstract<WiFi>());

}
