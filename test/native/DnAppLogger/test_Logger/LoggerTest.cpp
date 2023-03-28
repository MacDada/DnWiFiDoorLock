#include <unity.h>

#include "DnApp/Logger/Logger.h"

namespace {
    using DnApp::Logger::Logger;

    auto test_log_level_to_string() -> void {
        TEST_ASSERT_EQUAL_STRING(
            "debug",
            Logger::logLevelToString(Logger::LOG_LEVEL::DEBUG)
        );

        TEST_ASSERT_EQUAL_STRING(
            "info",
            Logger::logLevelToString(Logger::LOG_LEVEL::INFO)
        );

        TEST_ASSERT_EQUAL_STRING(
            "warning",
            Logger::logLevelToString(Logger::LOG_LEVEL::WARNING)
        );

        TEST_ASSERT_EQUAL_STRING(
            "error",
            Logger::logLevelToString(Logger::LOG_LEVEL::ERROR)
        );


        TEST_ASSERT_EQUAL_STRING(
            "critical",
            Logger::logLevelToString(Logger::LOG_LEVEL::CRITICAL)
        );
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_log_level_to_string);

    return UNITY_END();
}
