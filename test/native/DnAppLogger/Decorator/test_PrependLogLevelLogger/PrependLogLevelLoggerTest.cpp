#include <unity.h>

#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Decorator/PrependLogLevelLogger.h"
#include "DnApp/Logger/Endpoint/StringLogger.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Unity/asserts.h"
#include "../../../../_common/LoggerTest.h"

namespace {
    using DnApp::Logger::Logger;
    using DnApp::Logger::Endpoint::StringLogger;
    using DnApp::Logger::Decorator::PrependLogLevelLogger;

    const auto expectedOutputForFoo = ""
        "debug\n"
        "[debug] foo\n"
        "info\n"
        "[info] foo\n"
        "warning\n"
        "[warning] foo\n"
        "error\n"
        "[error] foo\n"
        "critical\n"
        "[critical] foo\n"
        "debug\n"
        "[debug] foo\n"
        "info\n"
        "[info] foo\n"
        "warning\n"
        "[warning] foo\n"
        "error\n"
        "[error] foo\n"
        "critical\n"
        "[critical] foo\n";

    auto stringLogger = StringLogger{};
    auto logger = PrependLogLevelLogger{stringLogger};

    auto test_it_is_a_Logger() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Logger, logger);
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
}

auto setUp() -> void {
    stringLogger.clear();
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Logger);
    RUN_TEST(test_logging_literals);
    RUN_TEST(test_logging_chars);
    RUN_TEST(test_logging_const_chars);
    RUN_TEST(test_logging_unique_ptr_of_chars);

    return UNITY_END();
}
