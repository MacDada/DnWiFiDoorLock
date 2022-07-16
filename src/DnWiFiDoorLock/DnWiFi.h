#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "Led.h"
#include "Hardware.h"
#include "Logger/ArduinoLogger.h"

namespace DnWiFiDoorLock {

    class DnWiFi final {
    public:
        DnWiFi(
            const char *ssid,
            const char *password,
            Led &led,
            Logger::ArduinoLogger &logger,
            Hardware &hardware
        );

        void connect();

    private:
        const char *ssid;
        const char *password;
        Led &led;
        Logger::ArduinoLogger &logger;
        Hardware &hardware;

        void waitForConnection();

        const char *wiFiConnectionStatusToString(uint8_t status);

        void informAboutConnectingIssue(int tries, int status);
    };

}
