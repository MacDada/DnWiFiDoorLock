#include <memory>

#include <functional>
#include <unity.h>
#include <vector>

#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Logger/Endpoint/StringLogger.h"
#include "DnApp/Logger/Decorator/SequenceLogger.h"
#include "DnApp/Unity/asserts.h"
#include "../../LoggerTest.h"

namespace {
    using DnApp::Logger::Logger;
    using DnApp::Logger::Endpoint::StringLogger;
    using DnApp::Logger::Decorator::SequenceLogger;

    StringLogger stringLogger1{};

    StringLogger stringLogger2{};

    const auto innerLoggers = std::vector<std::reference_wrapper<Logger>>{
        stringLogger1,
        stringLogger2
    };

    SequenceLogger logger{innerLoggers};

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

    void test_it_is_a_Logger() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Logger, &logger);
    }

    void test_it_works_with_no_inner_loggers() {
        const std::vector<std::reference_wrapper<Logger>> emptyVector;

        SequenceLogger loggerWithEmptyVector{emptyVector};

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            loggerWithEmptyVector,
            "foo"
        )
    }

    void test_logging_literals() {
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

    void test_logging_chars() {
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

    void test_logging_const_chars() {
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

    void test_logging_unique_ptr_of_chars() {
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
}

void setUp() {
    stringLogger1.clear();
    stringLogger2.clear();
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Logger);
    RUN_TEST(test_it_works_with_no_inner_loggers);
    RUN_TEST(test_logging_literals);
    RUN_TEST(test_logging_chars);
    RUN_TEST(test_logging_const_chars);
    RUN_TEST(test_logging_unique_ptr_of_chars);

    return UNITY_END();
}
