#include "MDNSSetupAndLoopAware.h"

namespace DnWiFiDoorLock::Arduino::Esp8266 {

    MDNSSetupAndLoopAware::MDNSSetupAndLoopAware(
        MDNSResponder &mdnsResponder,
        Logger &logger,
        const char *hostname
    ):
        mdnsResponder(mdnsResponder),
        logger(logger),
        hostname(hostname) {
    }

    void MDNSSetupAndLoopAware::onSetup() {
        if (mdnsResponder.begin(hostname)) {
            logger.log("MDNS responder started");
        } else {
            // todo: better error handling
            logger.log("There was a problem to start MDNS!");
        }
    }

    void MDNSSetupAndLoopAware::onLoop() {
        mdnsResponder.update();
    }

}
