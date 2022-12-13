#pragma once

#include <memory>

#include <unity.h>

#include "DnApp/Logger/Logger.h"
#include "DnApp/Unity/asserts.h"

#define DN_APP_LOGGER_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(message) {\
    logger.log(Logger::LOG_LEVEL::DEBUG, message);\
    logger.log(Logger::LOG_LEVEL::DEBUG, message);\
    logger.log(Logger::LOG_LEVEL::INFO, message);\
    logger.log(Logger::LOG_LEVEL::WARNING, message);\
    logger.log(Logger::LOG_LEVEL::ERROR, message);\
    logger.log(Logger::LOG_LEVEL::CRITICAL, message);\
    \
    logger.debug(message);\
    logger.info(message);\
    logger.warning(message);\
    logger.error(message);\
    logger.critical(message);\
}

namespace DnApp::Logger::LoggerTest {
    using DnApp::Logger::Logger;

    extern Logger &logger;

    void test_it_is_a_Logger() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Logger, &logger);
    }

    void test_logging_chars() {
        char foo[4] = "foo";

        DN_APP_LOGGER_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(foo);
    }

    void test_logging_const_chars() {
        const char foo[4] = "foo";

        DN_APP_LOGGER_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(foo);
    }

    void test_logging_unique_ptr_of_chars() {
        DN_APP_LOGGER_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            std::make_unique<char[]>(4)
        );
    }
}
