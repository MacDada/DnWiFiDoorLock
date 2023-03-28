#include <memory> // std::make_unique

#include <WString.h>
#include <unity.h>

#include "DnApp/Arduino/Logger/Endpoint/WithArduinoStringNullLogger.h"
#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Unity/asserts.h"
#include "../../../../../_common/LoggerTest.h"

namespace {
    using DnApp::Arduino::Logger::WithArduinoStringLogger;

    auto logger = DnApp::Arduino::Logger::Endpoint::WithArduinoStringNullLogger{};

    auto test_it_is_a_WithArduinoStringLogger() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(
            WithArduinoStringLogger,
            &logger
        );
    }

    auto test_logging_literals() -> void {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")
    }

    auto test_logging_chars() -> void {
        char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)
    }

    auto test_logging_const_chars() -> void {
        const char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)
    }

    auto test_logging_unique_ptr_of_chars() -> void {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            logger,
            std::make_unique<char[]>(4)
        )
    }

    auto test_logging_arduino_string() -> void {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            logger,
            String("foo")
        )
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_WithArduinoStringLogger);
    RUN_TEST(test_logging_literals);
    RUN_TEST(test_logging_chars);
    RUN_TEST(test_logging_const_chars);
    RUN_TEST(test_logging_unique_ptr_of_chars);
    RUN_TEST(test_logging_arduino_string);

    return UNITY_END();
}
