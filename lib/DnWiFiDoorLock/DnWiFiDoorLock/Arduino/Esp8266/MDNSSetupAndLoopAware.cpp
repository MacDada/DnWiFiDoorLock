#include "MDNSSetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266 {
    MDNSSetupAndLoopAware::MDNSSetupAndLoopAware(
        MDNSResponder &mdnsResponder,
        Logger &logger,
        const char *const hostname
    ):
        mdnsResponder(mdnsResponder),
        logger(logger),
        hostname(hostname) {
    }

    void MDNSSetupAndLoopAware::onSetup() {
        if (mdnsResponder.begin(hostname)) {
            logger.info(PSTR("MDNS responder started"));
        } else {
            // todo: better error handling
            logger.error(PSTR("There was a problem to start MDNS!"));
        }
    }

    void MDNSSetupAndLoopAware::onLoop() {
        mdnsResponder.update();
    }
}
