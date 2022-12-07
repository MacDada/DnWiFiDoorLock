#include <memory>

#include <unity.h>

#include "DnApp/Logger/Logger.h"
#include "DnApp/Logger/NullLogger.h"
#include "DnApp/Unity/asserts.h"

using DnApp::Logger::Logger;
using DnApp::Logger::NullLogger;

NullLogger logger;

void test_it_is_a_Logger() {
    TEST_ASSERT_INSTANCE_OF(Logger, &logger);
}

void test_logging_chars() {
    char foo[4] = "foo";

    logger.log(Logger::LOG_LEVEL::DEBUG, foo);
    logger.log(Logger::LOG_LEVEL::INFO, foo);
    logger.log(Logger::LOG_LEVEL::WARNING, foo);
    logger.log(Logger::LOG_LEVEL::ERROR, foo);
    logger.log(Logger::LOG_LEVEL::CRITICAL, foo);

    logger.debug(foo);
    logger.info(foo);
    logger.warning(foo);
    logger.error(foo);
    logger.critical(foo);
}

void test_logging_const_chars() {
    const char foo[4] = "foo";

    logger.log(Logger::LOG_LEVEL::DEBUG, foo);
    logger.log(Logger::LOG_LEVEL::INFO, foo);
    logger.log(Logger::LOG_LEVEL::WARNING, foo);
    logger.log(Logger::LOG_LEVEL::ERROR, foo);
    logger.log(Logger::LOG_LEVEL::CRITICAL, foo);

    logger.debug(foo);
    logger.info(foo);
    logger.warning(foo);
    logger.error(foo);
    logger.critical(foo);
}

auto make_unique_ptr_of_chars() {
    return std::make_unique<char[]>(4);
}

void test_logging_unique_ptr_of_chars() {
    logger.log(Logger::LOG_LEVEL::DEBUG, make_unique_ptr_of_chars());
    logger.log(Logger::LOG_LEVEL::INFO, make_unique_ptr_of_chars());
    logger.log(Logger::LOG_LEVEL::WARNING, make_unique_ptr_of_chars());
    logger.log(Logger::LOG_LEVEL::ERROR, make_unique_ptr_of_chars());
    logger.log(Logger::LOG_LEVEL::CRITICAL, make_unique_ptr_of_chars());

    logger.debug(make_unique_ptr_of_chars());
    logger.info(make_unique_ptr_of_chars());
    logger.warning(make_unique_ptr_of_chars());
    logger.error(make_unique_ptr_of_chars());
    logger.critical(make_unique_ptr_of_chars());
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Logger);
    RUN_TEST(test_logging_chars);
    RUN_TEST(test_logging_const_chars);
    RUN_TEST(test_logging_unique_ptr_of_chars);

    return UNITY_END();
}
