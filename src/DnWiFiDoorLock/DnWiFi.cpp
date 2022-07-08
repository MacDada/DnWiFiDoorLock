#include "DnWiFi.h"

using namespace DnWiFiDoorLock;

DnWiFi::DnWiFi(const char *ssid, const char *password, DnLed &led) {
    this->ssid = ssid;
    this->password = password;
    this->led = &led;
}

void DnWiFi::connect() {
    WiFi.begin(this->ssid, this->password);

    Serial.printf("\nWiFi selected: \"%s\"\n", this->ssid);
    Serial.print("Connecting");

    delay(1000);

    waitForConnection();

    Serial.print("\nConnected, IP address: ");
    Serial.println(WiFi.localIP());
}

void DnWiFi::waitForConnection() {
    int tries = 0;

    // todo: better error handling
    while (true) {
        int status = WiFi.status();

        if (WL_CONNECTED == status) {
            return;
        }

        delay(500);

        Serial.print(".");

        if (++tries > 20) {
            informAboutConnectingIssue(tries, status);
        }
    }
}

void DnWiFi::informAboutConnectingIssue(int tries, int status) {
    led->blinkFast(3);

    if (0 == tries % 5) {
        Serial.printf(
            "\nWiFi is still not connected, status: %s (%d)\n",
            wiFiConnectionStatusToString(status),
            (int) status
        );
    }
}

const char *DnWiFi::wiFiConnectionStatusToString(uint8_t status) {
    switch (status) {
        case WL_NO_SHIELD:
            return "WL_NO_SHIELD";
        case WL_IDLE_STATUS:
            return "WL_IDLE_STATUS";
        case WL_NO_SSID_AVAIL:
            return "WL_NO_SSID_AVAIL [invalid SSID?]";
        case WL_SCAN_COMPLETED:
            return "WL_SCAN_COMPLETED";
        case WL_CONNECTED:
            return "WL_CONNECTED";
        case WL_CONNECT_FAILED:
            return "WL_CONNECT_FAILED";
        case WL_CONNECTION_LOST:
            return "WL_CONNECTION_LOST";
        case WL_WRONG_PASSWORD:
            return "WL_WRONG_PASSWORD";
        case WL_DISCONNECTED:
            return "WL_DISCONNECTED";
        default:
            return "WL_UNKNOWN_STATUS";
    }
}
