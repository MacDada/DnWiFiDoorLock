#include <memory> // std::make_unique

#include <unity.h>

#include "DnApp/Logger/Endpoint/NullLogger.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Unity/asserts.h"
#include "../../../../_common/LoggerTest.h"

namespace {
    using DnApp::Logger::Logger;

    auto logger = DnApp::Logger::Endpoint::NullLogger{};

    auto test_it_is_a_Logger() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Logger, logger);
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
