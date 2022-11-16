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
            logger.log(Logger::LOG_LEVEL::INFO, "MDNS responder started");
        } else {
            // todo: better error handling
            logger.log(Logger::LOG_LEVEL::ERROR, "There was a problem to start MDNS!");
        }
    }

    void MDNSSetupAndLoopAware::onLoop() {
        mdnsResponder.update();
    }

}
