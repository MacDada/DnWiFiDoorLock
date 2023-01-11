#include "WiFi.h"

namespace {
    using DnApp::Common::Strings::format;
}

namespace DnWiFiDoorLock::Arduino::Esp82666::WiFi {
    WiFi::WiFi(
        const char *const ssid,
        const char *const password,
        DnWiFiDoorLock::Arduino::LedBlinker &ledBlinker,
        DnApp::Arduino::Logger::Logger &logger,
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

        logger.info(format(PSTR("WiFi selected: \"%s\""), this->ssid));

        // todo: this is probably casting the literal to String object
        //       - maybe not the best idea after all?
        logger.info(F("Connecting"));

        hardware.pause(1000);

        waitForConnection();

        logger.info(format(
            // todo: why does PSTR work here,
            //       even though I don't use any special FLASH methods in the format() function?
            //       * https://forum.arduino.cc/t/esp8266-f-macro-is-unnecessary-on-esp-chips/1075805/1
            //       * https://community.platformio.org/t/esp8266-arduino-f-macro-is-unnecessary-on-esp-chips/31399
            //       * https://discord.com/channels/583251190591258624/1062392340783829063/1062392340783829063
            PSTR("Connected, IP address: %s"),
            esp8266WiFi.localIP().toString().c_str()
        ));
    }

    void WiFi::waitForConnection() {
        int tries = 0;
        String connectingMessage{F("Connecting")};

        // todo: better error handling
        while (true) {
            int status = esp8266WiFi.status();

            if (WL_CONNECTED == status) {
                return;
            }

            hardware.pause(500);

            connectingMessage += F(".");

            logger.info(connectingMessage);

            if (++tries > 20) {
                informAboutConnectingIssue(tries, status);
            }
        }
    }

    void WiFi::informAboutConnectingIssue(const int tries, const int status) {
        ledBlinker.blinkFast(3);

        if (0 == tries % 5) {
            logger.warning(format(
                PSTR("WiFi is still not connected, status: %s (%d)"),
                wiFiConnectionStatusToString(status),
                status
            ));
        }
    }

    const char *WiFi::wiFiConnectionStatusToString(const uint8_t status) const {
        switch (status) {
            case WL_NO_SHIELD:
                return PSTR("WL_NO_SHIELD");
            case WL_IDLE_STATUS:
                return PSTR("WL_IDLE_STATUS");
            case WL_NO_SSID_AVAIL:
                return PSTR("WL_NO_SSID_AVAIL [invalid SSID?]");
            case WL_SCAN_COMPLETED:
                return PSTR("WL_SCAN_COMPLETED");
            case WL_CONNECTED:
                return PSTR("WL_CONNECTED");
            case WL_CONNECT_FAILED:
                return PSTR("WL_CONNECT_FAILED");
            case WL_CONNECTION_LOST:
                return PSTR("WL_CONNECTION_LOST");
            case WL_WRONG_PASSWORD:
                return PSTR("WL_WRONG_PASSWORD");
            case WL_DISCONNECTED:
                return PSTR("WL_DISCONNECTED");
            default:
                return PSTR("WL_UNKNOWN_STATUS");
        }
    }
}
