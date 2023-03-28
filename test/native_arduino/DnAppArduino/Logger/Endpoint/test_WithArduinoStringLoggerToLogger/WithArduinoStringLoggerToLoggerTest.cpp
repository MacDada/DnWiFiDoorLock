#include <WString.h>
#include <unity.h>

#include "DnApp/Arduino/Logger/Endpoint/WithArduinoStringLoggerToLogger.h"
#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Endpoint/StringLogger.h"
#include "DnApp/Unity/asserts.h"
#include "../../../../../_common/LoggerTest.h"

namespace {
    using DnApp::Arduino::Logger::Endpoint::WithArduinoStringLoggerToLogger;
    using DnApp::Arduino::Logger::WithArduinoStringLogger;
    using DnApp::Logger::Endpoint::StringLogger;

    const auto expectedOutputForFoo = ""
        "debug\n"
        "foo\n"
        "info\n"
        "foo\n"
        "warning\n"
        "foo\n"
        "error\n"
        "foo\n"
        "critical\n"
        "foo\n"
        "debug\n"
        "foo\n"
        "info\n"
        "foo\n"
        "warning\n"
        "foo\n"
        "error\n"
        "foo\n"
        "critical\n"
        "foo\n";

    auto stringLogger = StringLogger{};
    auto logger = WithArduinoStringLoggerToLogger{stringLogger};

    auto test_it_is_a_WithArduinoStringLogger() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(
            WithArduinoStringLogger,
            &logger
        );
    }

    auto test_logging_literals() -> void {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger.getContent()
        );
    }

    auto test_logging_chars() -> void {
        char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger.getContent()
        );
    }

    auto test_logging_const_chars() -> void {
        const char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger.getContent()
        );
    }

    auto test_logging_unique_ptr_of_chars() -> void {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            logger,
            DnApp::Common::Strings::makeUniquePtrOfChars("foo")
        )

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger.getContent()
        );
    }

    auto test_logging_arduino_string() -> void {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            logger,
            String("foo")
        )

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger.getContent()
        );
    }
}

auto setUp() -> void {
    stringLogger.clear();
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
