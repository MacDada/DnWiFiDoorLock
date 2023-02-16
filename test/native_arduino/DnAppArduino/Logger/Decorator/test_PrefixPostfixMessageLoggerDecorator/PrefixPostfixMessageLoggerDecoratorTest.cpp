#include <unity.h>
#include <WString.h>

#include "DnApp/Arduino/Logger/Decorator/PrefixPostfixMessageLoggerDecorator.h"
#include "DnApp/Arduino/Logger/WithArduinoStringLogger.h"
#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Endpoint/StringLogger.h"
#include "DnApp/Unity/asserts.h"
#include "../../../../../_common/LoggerTest.h"

namespace {
    using DnApp::Arduino::Logger::WithArduinoStringLogger;
    using DnApp::Logger::Endpoint::StringLogger;
    using DnApp::Arduino::Logger::Decorator::PrefixPostfixMessageLoggerDecorator;

    auto stringLogger = StringLogger{};

    auto logger = PrefixPostfixMessageLoggerDecorator{
        stringLogger,
        "the_prefix ",
        " the_postfix",
    };

    const auto expectedOutputForPrefixAndPostfix = ""
        "debug\n"
        "the_prefix foo the_postfix\n"
        "info\n"
        "the_prefix foo the_postfix\n"
        "warning\n"
        "the_prefix foo the_postfix\n"
        "error\n"
        "the_prefix foo the_postfix\n"
        "critical\n"
        "the_prefix foo the_postfix\n"
        "debug\n"
        "the_prefix foo the_postfix\n"
        "info\n"
        "the_prefix foo the_postfix\n"
        "warning\n"
        "the_prefix foo the_postfix\n"
        "error\n"
        "the_prefix foo the_postfix\n"
        "critical\n"
        "the_prefix foo the_postfix\n";

    void test_it_is_a_WithArduinoStringLogger() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(WithArduinoStringLogger, &logger);
    }

    void test_logging_with_empty_prefix_and_postfix() {
        auto loggerWithEmptyPrefixAndPostfix = PrefixPostfixMessageLoggerDecorator{
            stringLogger,
        };

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            loggerWithEmptyPrefixAndPostfix,
            "foo"
        )

        TEST_ASSERT_EQUAL_STRING(
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
            "foo\n",
            stringLogger.getContent()
        );
    };

    void test_logging_with_prefix() {
        auto loggerWithPrefix = PrefixPostfixMessageLoggerDecorator{
            stringLogger,
            "prefix ",
        };

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(loggerWithPrefix, "foo")

        TEST_ASSERT_EQUAL_STRING(
            "debug\n"
            "prefix foo\n"
            "info\n"
            "prefix foo\n"
            "warning\n"
            "prefix foo\n"
            "error\n"
            "prefix foo\n"
            "critical\n"
            "prefix foo\n"
            "debug\n"
            "prefix foo\n"
            "info\n"
            "prefix foo\n"
            "warning\n"
            "prefix foo\n"
            "error\n"
            "prefix foo\n"
            "critical\n"
            "prefix foo\n",
            stringLogger.getContent()
        );
    };

    void test_logging_with_postfix() {
        auto loggerWithPostfix = PrefixPostfixMessageLoggerDecorator{
            stringLogger,
            "",
            " postfix",
        };

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(loggerWithPostfix, "foo")

        TEST_ASSERT_EQUAL_STRING(
            "debug\n"
            "foo postfix\n"
            "info\n"
            "foo postfix\n"
            "warning\n"
            "foo postfix\n"
            "error\n"
            "foo postfix\n"
            "critical\n"
            "foo postfix\n"
            "debug\n"
            "foo postfix\n"
            "info\n"
            "foo postfix\n"
            "warning\n"
            "foo postfix\n"
            "error\n"
            "foo postfix\n"
            "critical\n"
            "foo postfix\n",
            stringLogger.getContent()
        );
    };

    void test_logging_literals() {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForPrefixAndPostfix,
            stringLogger.getContent()
        );
    }

    void test_logging_chars() {
        char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForPrefixAndPostfix,
            stringLogger.getContent()
        );
    }

    void test_logging_const_chars() {
        const char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForPrefixAndPostfix,
            stringLogger.getContent()
        );
    }

    void test_logging_unique_ptr_of_chars() {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            logger,
            DnApp::Common::Strings::makeUniquePtrOfChars("foo")
        )

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForPrefixAndPostfix,
            stringLogger.getContent()
        );
    }

    void test_logging_arduino_string() {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            logger,
            String("foo")
        )

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForPrefixAndPostfix,
            stringLogger.getContent()
        );
    }
}

void setUp() {
    stringLogger.clear();
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_WithArduinoStringLogger);
    RUN_TEST(test_logging_with_empty_prefix_and_postfix);
    RUN_TEST(test_logging_with_prefix);
    RUN_TEST(test_logging_with_postfix);
    RUN_TEST(test_logging_literals);
    RUN_TEST(test_logging_chars);
    RUN_TEST(test_logging_const_chars);
    RUN_TEST(test_logging_unique_ptr_of_chars);
    RUN_TEST(test_logging_arduino_string);

    return UNITY_END();
}
