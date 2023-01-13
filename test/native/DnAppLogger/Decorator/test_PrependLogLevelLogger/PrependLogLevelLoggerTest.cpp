#include <unity.h>

#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Decorator/PrependLogLevelLogger.h"
#include "DnApp/Logger/Endpoint/StringLogger.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Unity/asserts.h"
#include "../../LoggerTest.h"

namespace {
    using DnApp::Logger::Logger;
    using DnApp::Logger::Endpoint::StringLogger;
    using DnApp::Logger::Decorator::PrependLogLevelLogger;

    StringLogger stringLogger{};
    PrependLogLevelLogger logger{stringLogger};

    void test_it_is_a_Logger() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Logger, &logger);
    }

    void test_logging_literals() {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS("foo")

        TEST_ASSERT_EQUAL_STRING(
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
            "[critical] foo\n",
            stringLogger.getContent()
        );
    }

    void test_logging_chars() {
        char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(foo)

        TEST_ASSERT_EQUAL_STRING(
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
            "[critical] foo\n",
            stringLogger.getContent()
        );
    }

    void test_logging_const_chars() {
        const char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(foo)

        TEST_ASSERT_EQUAL_STRING(
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
            "[critical] foo\n",
            stringLogger.getContent()
        );
    }

    void test_logging_unique_ptr_of_chars() {
        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            DnApp::Common::Strings::makeUniquePtrOfChars("foo")
        )

        TEST_ASSERT_EQUAL_STRING(
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
            "[critical] foo\n",
            stringLogger.getContent()
        );
    }
}

void setUp() {
    stringLogger.clear();
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
