#include <memory>

#include <unity.h>

#include "DnApp/Logger/Endpoint/NullLogger.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Unity/asserts.h"
#include "../../LoggerTest.h"

namespace {
    using DnApp::Logger::Logger;

    DnApp::Logger::Endpoint::NullLogger logger;

    void test_it_is_a_Logger() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Logger, &logger);
    }

    void test_logging_literals() {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")
    }

    void test_logging_chars() {
        char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)
    }

    void test_logging_const_chars() {
        const char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)
    }

    void test_logging_unique_ptr_of_chars() {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            logger,
            std::make_unique<char[]>(4)
        )
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Logger);
    RUN_TEST(test_logging_literals);
    RUN_TEST(test_logging_chars);
    RUN_TEST(test_logging_const_chars);
    RUN_TEST(test_logging_unique_ptr_of_chars);

    return UNITY_END();
}
