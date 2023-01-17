#include <memory>

#include <WString.h>
#include <unity.h>

#include "DnApp/Arduino/Logger/Endpoint/WithArduinoStringNullLogger.h"
#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Unity/asserts.h"
#include "../../../../../_common/LoggerTest.h"

namespace {
    using DnApp::Arduino::Logger::WithArduinoStringLogger;

    DnApp::Arduino::Logger::Endpoint::WithArduinoStringNullLogger logger{};

    void test_it_is_a_WithArduinoStringLogger() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(
            WithArduinoStringLogger,
            &logger
        );
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

    void test_logging_arduino_string() {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            logger,
            String("foo")
        )
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_WithArduinoStringLogger);
    RUN_TEST(test_logging_literals);
    RUN_TEST(test_logging_chars);
    RUN_TEST(test_logging_const_chars);
    RUN_TEST(test_logging_unique_ptr_of_chars);
    RUN_TEST(test_logging_arduino_string);

    return UNITY_END();
}
