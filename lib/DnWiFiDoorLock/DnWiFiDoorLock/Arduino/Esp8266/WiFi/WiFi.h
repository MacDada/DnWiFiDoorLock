#pragma once

#include <type_traits>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WString.h>

#include "DnApp/Logger/Logger.h"
#include "DnApp/Common/Strings.h"
#include "DnWiFiDoorLock/Arduino/Hardware.h"
#include "DnWiFiDoorLock/Arduino/LedBlinker.h"
#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Esp82666::WiFi {
    class WiFi final:
        public DnWiFiDoorLock::Arduino::SetupAndLoopAware {
    public:
        WiFi(
            const char* const ssid,
            const char* const password,
            DnWiFiDoorLock::Arduino::LedBlinker& ledBlinker,
            DnApp::Logger::Logger& logger,
            const DnWiFiDoorLock::Arduino::Hardware& hardware,
            ESP8266WiFiClass& esp8266WiFi
        ):
            ssid{ssid},
            password{password},
            ledBlinker{ledBlinker},
            logger{logger},
            hardware{hardware},
            esp8266WiFi{esp8266WiFi} {
        }

        void onSetup() override {
            connect();
        }

        void onLoop() override {
            watchForDisconnection();
        }
    private:
        const char* const ssid;

        const char* const password;

        DnWiFiDoorLock::Arduino::LedBlinker& ledBlinker;

        DnApp::Logger::Logger& logger;

        const DnWiFiDoorLock::Arduino::Hardware& hardware;

        ESP8266WiFiClass& esp8266WiFi;

        bool disconnected = false;

        static
        constexpr
        auto format = DnApp::Common::Strings::format;

        void connect() {
            esp8266WiFi.begin(this->ssid, this->password);

            logger.info(format(PSTR("WiFi selected: \"%s\""), this->ssid));

            logger.info(PSTR("Connecting"));

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

        void waitForConnection() {
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

                logger.info(connectingMessage.c_str());

                if (++tries > 20) {
                    informAboutConnectingIssue(tries, status);
                }
            }
        }

        void informAboutConnectingIssue(const int tries, const int status) {
            ledBlinker.blinkFast(3);

            if (0 == tries % 5) {
                logger.warning(format(
                    PSTR("WiFi is still not connected, status: %s (%d)"),
                    wiFiConnectionStatusToString(status),
                    status
                ));
            }
        }

        void watchForDisconnection() {
            if (!esp8266WiFi.isConnected()) {
                onDisconnected();
            } else if (disconnected) {
                onReconnected();
            }
        }

        void onDisconnected() {
            if (!disconnected) {
                disconnected = true;

                const uint8_t status = esp8266WiFi.status();

                logger.error(format(
                    PSTR("WiFi disconnected! Status: %s (%d)"),
                    wiFiConnectionStatusToString(status),
                    status
                ));
            }

            ledBlinker.blinkFast(2);
        }

        void onReconnected() {
            disconnected = false;

            logger.info(PSTR("WiFi reconnected!"));
        }

        const char* wiFiConnectionStatusToString(const uint8_t status) const {
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
    };

    static_assert(!std::is_abstract<WiFi>());
}
