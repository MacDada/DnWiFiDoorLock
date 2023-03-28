#include <unity.h>

#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Decorator/LogLevelThresholdFilteringLogger.h"
#include "DnApp/Logger/Endpoint/StringLogger.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Unity/asserts.h"
#include "../../../../_common/LoggerTest.h"

namespace {
    using DnApp::Logger::Logger;
    using DnApp::Logger::Endpoint::StringLogger;
    using DnApp::Logger::Decorator::LogLevelThresholdFilteringLogger;

    auto stringLogger = StringLogger{};

    auto test_it_is_a_Logger() -> void {
        auto logger = LogLevelThresholdFilteringLogger{stringLogger};

        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Logger, &logger);
    }

    auto test_threshold_is_debug_by_default() -> void {
        auto logger = LogLevelThresholdFilteringLogger{stringLogger};

        TEST_ASSERT_EQUAL_INT(
            Logger::LOG_LEVEL::DEBUG,
            logger.getThreshold()
        );
    }

    auto test_logging_literals() -> void {
        auto logger = LogLevelThresholdFilteringLogger{stringLogger};

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

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
    }

    auto test_logging_chars() -> void {
        auto logger = LogLevelThresholdFilteringLogger{stringLogger};

        char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)

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
    }

    auto test_logging_const_chars() -> void {
        auto logger = LogLevelThresholdFilteringLogger{stringLogger};

        const char foo[4] = "foo";

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, foo)

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
    }

    auto test_logging_unique_ptr_of_chars() -> void {
        auto logger = LogLevelThresholdFilteringLogger{stringLogger};

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(
            logger,
            DnApp::Common::Strings::makeUniquePtrOfChars("foo")
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
    }

    auto test_debug_threshold_can_be_configured() -> void {
        auto logger = LogLevelThresholdFilteringLogger{
            stringLogger,
            Logger::LOG_LEVEL::DEBUG
        };

        TEST_ASSERT_EQUAL_INT(
            Logger::LOG_LEVEL::DEBUG,
            logger.getThreshold()
        );

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

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
    }

    auto test_info_threshold_can_be_configured() -> void {
        auto logger = LogLevelThresholdFilteringLogger{
            stringLogger,
            Logger::LOG_LEVEL::INFO
        };

        TEST_ASSERT_EQUAL_INT(
            Logger::LOG_LEVEL::INFO,
            logger.getThreshold()
        );

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

        TEST_ASSERT_EQUAL_STRING(
            "info\n"
            "foo\n"
            "warning\n"
            "foo\n"
            "error\n"
            "foo\n"
            "critical\n"
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
    }

    auto test_warning_threshold_can_be_configured() -> void {
        auto logger = LogLevelThresholdFilteringLogger{
            stringLogger,
            Logger::LOG_LEVEL::WARNING
        };

        TEST_ASSERT_EQUAL_INT(
            Logger::LOG_LEVEL::WARNING,
            logger.getThreshold()
        );

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

        TEST_ASSERT_EQUAL_STRING(
            "warning\n"
            "foo\n"
            "error\n"
            "foo\n"
            "critical\n"
            "foo\n"
            "warning\n"
            "foo\n"
            "error\n"
            "foo\n"
            "critical\n"
            "foo\n",
            stringLogger.getContent()
        );
    }

    auto test_error_threshold_can_be_configured() -> void {
        auto logger = LogLevelThresholdFilteringLogger{
            stringLogger,
            Logger::LOG_LEVEL::ERROR
        };

        TEST_ASSERT_EQUAL_INT(
            Logger::LOG_LEVEL::ERROR,
            logger.getThreshold()
        );

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

        TEST_ASSERT_EQUAL_STRING(
            "error\n"
            "foo\n"
            "critical\n"
            "foo\n"
            "error\n"
            "foo\n"
            "critical\n"
            "foo\n",
            stringLogger.getContent()
        );
    }

    auto test_critical_threshold_can_be_configured() -> void {
        auto logger = LogLevelThresholdFilteringLogger{
            stringLogger,
            Logger::LOG_LEVEL::CRITICAL
        };

        TEST_ASSERT_EQUAL_INT(
            Logger::LOG_LEVEL::CRITICAL,
            logger.getThreshold()
        );

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

        TEST_ASSERT_EQUAL_STRING(
            "critical\n"
            "foo\n"
            "critical\n"
            "foo\n",
            stringLogger.getContent()
        );
    }

    auto test_threshold_can_be_set() -> void {
        auto logger = LogLevelThresholdFilteringLogger{
            stringLogger,
            Logger::LOG_LEVEL::CRITICAL
        };

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

        logger.setThreshold(Logger::LOG_LEVEL::WARNING);

        TEST_ASSERT_EQUAL_INT(
            Logger::LOG_LEVEL::WARNING,
            logger.getThreshold()
        );

        DN_APP_LOGGER_TEST_ALL_LOG_METHODS_AND_LEVELS(logger, "foo")

        TEST_ASSERT_EQUAL_STRING(
            "critical\n"
            "foo\n"
            "critical\n"
            "foo\n"
            "warning\n"
            "foo\n"
            "error\n"
            "foo\n"
            "critical\n"
            "foo\n"
            "warning\n"
            "foo\n"
            "error\n"
            "foo\n"
            "critical\n"
            "foo\n",
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
    RUN_TEST(test_threshold_is_debug_by_default);
    RUN_TEST(test_logging_literals);
    RUN_TEST(test_logging_chars);
    RUN_TEST(test_logging_const_chars);
    RUN_TEST(test_logging_unique_ptr_of_chars);
    RUN_TEST(test_debug_threshold_can_be_configured);
    RUN_TEST(test_info_threshold_can_be_configured);
    RUN_TEST(test_warning_threshold_can_be_configured);
    RUN_TEST(test_error_threshold_can_be_configured);
    RUN_TEST(test_critical_threshold_can_be_configured);
    RUN_TEST(test_threshold_can_be_set);

    return UNITY_END();
}
