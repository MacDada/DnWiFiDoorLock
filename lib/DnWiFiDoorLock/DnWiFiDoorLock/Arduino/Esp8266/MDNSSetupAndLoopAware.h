#pragma once

#include <type_traits> // std::is_abstract

#include <ESP8266mDNS.h>
#include <WString.h>

#include "DnApp/Arduino/Kernel/SetupAndLoopAware.h"
#include "DnApp/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Esp8266 {
    class MDNSSetupAndLoopAware final:
        public DnApp::Arduino::Kernel::SetupAndLoopAware {
    private:
        using MDNSResponder = esp8266::MDNSImplementation::MDNSResponder;
        using Logger = DnApp::Logger::Logger;
    public:
        explicit
        MDNSSetupAndLoopAware(
            MDNSResponder& mdnsResponder,
            Logger& logger,
            const char* const hostname
        ):
            mdnsResponder{mdnsResponder},
            logger{logger},
            hostname{hostname} {
        }

        auto onSetup() -> void override {
            if (mdnsResponder.begin(hostname)) {
                logger.info(PSTR("MDNS responder started"));
            } else {
                // todo: better error handling
                logger.error(PSTR("There was a problem to start MDNS!"));
            }
        }

        auto onLoop() -> void override {
            mdnsResponder.update();
        }
    private:
        MDNSResponder& mdnsResponder;

        Logger& logger;

        const char* const hostname;
    };

    static_assert(!std::is_abstract<MDNSSetupAndLoopAware>());
}
