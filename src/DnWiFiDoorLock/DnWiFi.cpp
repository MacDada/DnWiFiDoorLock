#include "DnWiFi.h"
#include "Tools.h"

namespace DnWiFiDoorLock {

    DnWiFi::DnWiFi(
        const char *ssid,
        const char *password,
        Led &led,
        Logger::ArduinoLogger &logger,
        Hardware &hardware
    ):
        ssid(ssid),
        password(password),
        led(led),
        logger(logger),
        hardware(hardware) {
    }

    void DnWiFi::connect() {
        WiFi.begin(this->ssid, this->password);

        logger.log(Tools::format("WiFi selected: \"%s\"", this->ssid));
        logger.log("Connecting");

        hardware.pause(1000);

        waitForConnection();

        logger.log(Tools::format("Connected, IP address: %s", WiFi.localIP().toString().c_str()));
    }

    void DnWiFi::waitForConnection() {
        int tries = 0;
        String connectingMessage = "Connecting";

        // todo: better error handling
        while (true) {
            int status = WiFi.status();

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

    void DnWiFi::informAboutConnectingIssue(int tries, int status) {
        led.blinkFast(3);

        if (0 == tries % 5) {
            logger.log(Tools::format(
                "WiFi is still not connected, status: %s (%d)",
                wiFiConnectionStatusToString(status),
                (int) status
            ));
        }
    }

    // todo: `const uint8_t &status`?
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

}
