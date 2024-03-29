#include <unity.h>

#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Logger/Endpoint/StringLogger.h"
#include "DnApp/Logger/Decorator/PrefixPostfixMessageLoggerDecorator.h"
#include "DnApp/Unity/asserts.h"
#include "../../../../_common/LoggerTest.h"

namespace {
    using DnApp::Logger::Logger;
    using DnApp::Logger::Endpoint::StringLogger;
    using DnApp::Logger::Decorator::PrefixPostfixMessageLoggerDecorator;

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

    auto test_it_is_a_Logger() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Logger, logger);
    }

    auto test_logging_with_empty_prefix_and_postfix() -> void {
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

    auto test_logging_with_prefix() -> void {
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

    auto test_logging_with_postfix() -> void {
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

    auto test_logging_literals() -> void {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForPrefixAndPostfix,
            stringLogger.getContent()
        );
    }

    auto test_logging_chars() -> void {
        char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForPrefixAndPostfix,
            stringLogger.getContent()
        );
    }

    auto test_logging_const_chars() -> void {
        const char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForPrefixAndPostfix,
            stringLogger.getContent()
        );
    }

    auto test_logging_unique_ptr_of_chars() -> void {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            logger,
            DnApp::Common::Strings::makeUniquePtrOfChars("foo")
        )

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForPrefixAndPostfix,
            stringLogger.getContent()
        );
    }
}

auto setUp() -> void {
    stringLogger.clear();
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Logger);
    RUN_TEST(test_logging_with_empty_prefix_and_postfix);
    RUN_TEST(test_logging_with_prefix);
    RUN_TEST(test_logging_with_postfix);
    RUN_TEST(test_logging_literals);
    RUN_TEST(test_logging_chars);
    RUN_TEST(test_logging_const_chars);
    RUN_TEST(test_logging_unique_ptr_of_chars);

    return UNITY_END();
}
