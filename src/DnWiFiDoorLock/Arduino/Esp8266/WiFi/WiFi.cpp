#include "WiFi.h"

namespace DnWiFiDoorLock::Arduino::Esp82666::WiFi {

    WiFi::WiFi(
        const char *const ssid,
        const char *const password,
        const DnWiFiDoorLock::Arduino::LedBlinker &ledBlinker,
        DnWiFiDoorLock::Arduino::Logger::Logger &logger,
        const DnWiFiDoorLock::Arduino::Hardware &hardware,
        ESP8266WiFiClass &esp8266WiFi
    ):
        ssid(ssid),
        password(password),
        ledBlinker(ledBlinker),
        logger(logger),
        hardware(hardware),
        esp8266WiFi(esp8266WiFi) {
    }

    void WiFi::onSetup() {
        connect();
    }

    void WiFi::onLoop() {
        if (!esp8266WiFi.isConnected()) {
            ledBlinker.blinkFast(2);
        }
    }

    void WiFi::connect() {
        esp8266WiFi.begin(this->ssid, this->password);

        logger.log(Logger::Logger::LOG_LEVEL::INFO, Tools::format("WiFi selected: \"%s\"", this->ssid));
        logger.log(Logger::Logger::LOG_LEVEL::INFO, "Connecting");

        hardware.pause(1000);

        waitForConnection();

        logger.log(Logger::Logger::LOG_LEVEL::INFO, Tools::format(
            "Connected, IP address: %s",
            esp8266WiFi.localIP().toString().c_str()
        ));
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

            logger.log(Logger::Logger::LOG_LEVEL::INFO, connectingMessage);

            if (++tries > 20) {
                informAboutConnectingIssue(tries, status);
            }
        }
    }

    void WiFi::informAboutConnectingIssue(const int tries, const int status) {
        ledBlinker.blinkFast(3);

        if (0 == tries % 5) {
            logger.log(Logger::Logger::LOG_LEVEL::WARNING, Tools::format(
                "WiFi is still not connected, status: %s (%d)",
                wiFiConnectionStatusToString(status),
                (int) status
            ));
        }
    }

    const char *WiFi::wiFiConnectionStatusToString(const uint8_t status) const {
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
