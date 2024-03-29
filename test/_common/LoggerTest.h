#pragma once

#include "DnApp/Logger/Logger.h"

#define DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, message) {\
    logger.log(DnApp::Logger::Logger::LOG_LEVEL::DEBUG, message);\
    logger.log(DnApp::Logger::Logger::LOG_LEVEL::INFO, message);\
    logger.log(DnApp::Logger::Logger::LOG_LEVEL::WARNING, message);\
    logger.log(DnApp::Logger::Logger::LOG_LEVEL::ERROR, message);\
    logger.log(DnApp::Logger::Logger::LOG_LEVEL::CRITICAL, message);\
    \
    logger.debug(message);\
    logger.info(message);\
    logger.warning(message);\
    logger.error(message);\
    logger.critical(message);\
}
