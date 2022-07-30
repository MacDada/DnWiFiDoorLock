#pragma once

#include <type_traits>

#include <ESP8266mDNS.h>

#include "DnWiFiDoorLock/Arduino/SetupAndLoopAware.h"
#include "DnWiFiDoorLock/Logger/Logger.h"

namespace DnWiFiDoorLock::Arduino::Esp8266 {

    using esp8266::MDNSImplementation::MDNSResponder;
    using DnWiFiDoorLock::Logger::Logger;

    class MDNSSetupAndLoopAware final: public SetupAndLoopAware {
    public:
        explicit MDNSSetupAndLoopAware(
            MDNSResponder &mdnsResponder,
            Logger &logger,
            const char *hostname
        );

        void onSetup() override;

        void onLoop() override;

    private:
        MDNSResponder &mdnsResponder;

        Logger &logger;

        const char *hostname;
    };

    static_assert(!std::is_abstract<MDNSSetupAndLoopAware>());

}
