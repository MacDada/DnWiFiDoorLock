#pragma once

#include <cstdint> // uint16_t
#include <type_traits> // std::is_abstract

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WString.h>

#include "DnApp/Arduino/Hardware/Board.h"
#include "DnApp/Arduino/Hardware/LedBlinker.h"
#include "DnApp/Arduino/Kernel/SetupAndLoopAware.h"
#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Decorator/PrefixPostfixMessageLoggerDecorator.h"
#include "DnApp/Logger/Logger.h"

namespace DnApp::Esp::Esp8266 {
    class WiFiSetupAndLoopAware final:
        public DnApp::Arduino::Kernel::SetupAndLoopAware {
    private:
        using PrefixingLogger = DnApp
            ::Logger
            ::Decorator
            ::PrefixPostfixMessageLoggerDecorator;
    public:
        WiFiSetupAndLoopAware(
            const char* const ssid,
            const char* const password,
            DnApp::Arduino::Hardware::LedBlinker& ledBlinker,
            DnApp::Logger::Logger& logger,
            DnApp::Arduino::Hardware::Board& board,
            ESP8266WiFiClass& esp8266WiFi
        ):
            ssid{ssid},
            password{password},
            ledBlinker{ledBlinker},
            logger{PrefixingLogger{logger, PSTR("WiFi: ")}},
            board{board},
            esp8266WiFi{esp8266WiFi} {
        }

        auto onSetup() -> void override {
            connect();
        }

        auto onLoop() -> void override {
            watchForDisconnection();
        }
    private:
        const char* const ssid;

        const char* const password;

        DnApp::Arduino::Hardware::LedBlinker& ledBlinker;

        PrefixingLogger logger;

        DnApp::Arduino::Hardware::Board& board;

        ESP8266WiFiClass& esp8266WiFi;

        bool disconnected = false;

        static
        constexpr
        const
        auto format = DnApp::Common::Strings::format;

        auto connect() -> void {
            esp8266WiFi.begin(this->ssid, this->password);

            logger.info(format(PSTR("Selected: \"%s\""), this->ssid));

            waitForConnection();

            logger.info(format(
                PSTR("Connected, IP address: %s"),
                esp8266WiFi.localIP().toString().c_str()
            ));
        }

        auto waitForConnection() -> void {
            String connectingMessage{PSTR("Connecting")};

            logger.info(connectingMessage.c_str());

            auto tries = uint16_t{0};

            while (true) {
                const auto status = esp8266WiFi.status();

                if (WL_CONNECTED == status) {
                    return;
                }

                board.pause(500);

                connectingMessage += PSTR(".");

                logger.info(connectingMessage.c_str());

                if (++tries > 20) {
                    informAboutConnectingIssue(tries, status);
                }
            }
        }

        auto informAboutConnectingIssue(const uint16_t tries, const int status) -> void {
            ledBlinker.blinkFast(3);

            if (0 == tries % 5) {
                logger.warning(format(
                    PSTR("Still not connected, status: %s (%d)"),
                    wiFiConnectionStatusToString(status),
                    status
                ));
            }
        }

        auto watchForDisconnection() -> void {
            if (!esp8266WiFi.isConnected()) {
                onDisconnected();
            } else if (disconnected) {
                onReconnected();
            }
        }

        auto onDisconnected() -> void {
            if (!disconnected) {
                disconnected = true;

                const auto status = esp8266WiFi.status();

                logger.error(format(
                    PSTR("Disconnected! Status: %s (%d)"),
                    wiFiConnectionStatusToString(status),
                    status
                ));
            }

            ledBlinker.blinkFast(2);
        }

        auto onReconnected() -> void {
            disconnected = false;

            logger.info(PSTR("Reconnected!"));
        }

        auto wiFiConnectionStatusToString(const uint8_t status) const -> const char* {
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

    static_assert(!std::is_abstract<WiFiSetupAndLoopAware>());
}
