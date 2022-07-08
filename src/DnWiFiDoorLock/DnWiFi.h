#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "DnLed.h"

namespace DnWiFiDoorLock {
    class DnWiFi {
    public:
        DnWiFi(const char *ssid, const char *password, DnLed &led);

        void connect();

    private:
        const char *ssid;
        const char *password;
        DnLed *led;

        void waitForConnection();

        const char *wiFiConnectionStatusToString(uint8_t status);

        void informAboutConnectingIssue(int tries, int status);
    };
}
