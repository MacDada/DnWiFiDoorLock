#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "Led.h"
#include "Hardware.h"
#include "Logger/ArduinoLogger.h"

namespace DnWiFiDoorLock {

    class WiFi final {
    public:
        WiFi(
            const char *ssid,
            const char *password,
            Led &led,
            Logger::ArduinoLogger &logger,
            Hardware &hardware,
            ESP8266WiFiClass &esp8266WiFi
        );

        void connect();

    private:
        const char *ssid;
        const char *password;
        Led &led;
        Logger::ArduinoLogger &logger;
        Hardware &hardware;
        ESP8266WiFiClass &esp8266WiFi;

        void waitForConnection();

        const char *wiFiConnectionStatusToString(uint8_t status);

        void informAboutConnectingIssue(int tries, int status);
    };

}
