#include "WiFi.h"
#include "Tools.h"

namespace DnWiFiDoorLock {

    WiFi::WiFi(
        const char *ssid,
        const char *password,
        DnWiFiDoorLock::Arduino::Led &led,
        Logger::ArduinoLogger &logger,
        DnWiFiDoorLock::Arduino::Hardware &hardware,
        ESP8266WiFiClass &esp8266WiFi
    ):
        ssid(ssid),
        password(password),
        led(led),
        logger(logger),
        hardware(hardware),
        esp8266WiFi(esp8266WiFi) {
    }

    void WiFi::onSetup() {
        connect();
    }

    void WiFi::onLoop() {
        // do nothing
    }

    void WiFi::connect() {
        esp8266WiFi.begin(this->ssid, this->password);

        logger.log(Tools::format("WiFi selected: \"%s\"", this->ssid).get());
        logger.log("Connecting");

        hardware.pause(1000);

        waitForConnection();

        logger.log(Tools::format("Connected, IP address: %s", esp8266WiFi.localIP().toString().c_str()).get());
    }

    void WiFi::waitForConnection() {
        int tries = 0;
        String connectingMessage = "Connecting";

        // todo: better error handling
        while (true) {
            int status = esp8266WiFi.status();

            if (WL_CONNECTED == status) {
                return;
            }

            hardware.pause(500);

            connectingMessage += ".";

            logger.log(connectingMessage);

            if (++tries > 20) {
                informAboutConnectingIssue(tries, status);
            }
        }
    }

    void WiFi::informAboutConnectingIssue(int tries, int status) {
        led.blinkFast(3);

        if (0 == tries % 5) {
            logger.log(Tools::format(
                "WiFi is still not connected, status: %s (%d)",
                wiFiConnectionStatusToString(status),
                (int) status
            ).get());
        }
    }

    // todo: `const uint8_t &status`?
    const char *WiFi::wiFiConnectionStatusToString(uint8_t status) {
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

}
