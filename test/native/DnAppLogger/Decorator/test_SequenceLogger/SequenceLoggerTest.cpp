#include <array>
#include <functional> // std::reference_wrapper
#include <span>
#include <vector>

#include <unity.h>

#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Logger/Endpoint/StringLogger.h"
#include "DnApp/Logger/Decorator/SequenceLogger.h"
#include "DnApp/Unity/asserts.h"
#include "../../../../_common/LoggerTest.h"

namespace {
    using DnApp::Logger::Logger;
    using DnApp::Logger::Endpoint::StringLogger;
    using DnApp::Logger::Decorator::SequenceLogger;

    auto stringLogger1 = StringLogger{};

    auto stringLogger2 = StringLogger{};

    const auto innerLoggers = std::vector<std::reference_wrapper<Logger>>{
        stringLogger1,
        stringLogger2
    };

    auto logger = SequenceLogger{innerLoggers};

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

    auto test_it_is_a_Logger() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Logger, &logger);
    }

    auto test_it_works_with_no_inner_loggers() -> void {
        const auto emptyVector = std::vector<std::reference_wrapper<Logger>>{};

        SequenceLogger loggerWithEmptyVector{emptyVector};

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            loggerWithEmptyVector,
            "foo"
        )
    }

    auto test_logging_literals() -> void {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger1.getContent()
        );

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger2.getContent()
        );
    }

    auto test_logging_chars() -> void {
        char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger1.getContent()
        );

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger2.getContent()
        );
    }

    auto test_logging_const_chars() -> void {
        const char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger1.getContent()
        );

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger2.getContent()
        );
    }

    auto test_logging_unique_ptr_of_chars() -> void {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            logger,
            DnApp::Common::Strings::makeUniquePtrOfChars("foo")
        )

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger1.getContent()
        );

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger2.getContent()
        );
    }

    auto test_it_works_with_empty_array() -> void {
        const auto emptyArray = std::array<std::reference_wrapper<Logger>, 0>{};

        SequenceLogger loggerWithEmptyArray{emptyArray};

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            loggerWithEmptyArray,
            "foo"
        )
    }

    auto test_logging_literals_with_array() -> void {
        const auto theArray = std::array<std::reference_wrapper<Logger>, 2>{
            stringLogger1,
            stringLogger2
        };

        auto loggerWithArray = SequenceLogger{theArray};

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(loggerWithArray, "foo")

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger1.getContent()
        );

        TEST_ASSERT_EQUAL_STRING(
            expectedOutputForFoo,
            stringLogger2.getContent()
        );
    }
}

auto setUp() -> void {
    stringLogger1.clear();
    stringLogger2.clear();
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Logger);
    RUN_TEST(test_it_works_with_no_inner_loggers);
    RUN_TEST(test_logging_literals);
    RUN_TEST(test_logging_chars);
    RUN_TEST(test_logging_const_chars);
    RUN_TEST(test_logging_unique_ptr_of_chars);
    RUN_TEST(test_it_works_with_empty_array);
    RUN_TEST(test_logging_literals_with_array);

    return UNITY_END();
}
