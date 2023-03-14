#include <unity.h>

#include "DnApp/Common/Strings.h"
#include "DnApp/Logger/Endpoint/StringLogger.h"
#include "DnApp/Logger/Logger.h"
#include "DnApp/Unity/asserts.h"

namespace {
    using DnApp::Logger::Logger;

    DnApp::Logger::Endpoint::StringLogger logger{};

    void test_it_is_a_Logger() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(DnApp::Logger::Logger, &logger);
    }

    void test_it_is_empty_at_start() {
        TEST_ASSERT_EQUAL_STRING("", logger.getContent());
    }

    void test_clear() {
        logger.warning("foo");
        logger.error("bar");

        logger.clear();

        TEST_ASSERT_EQUAL_STRING("", logger.getContent());
    }

    void test_logging_literals() {
        logger.log(Logger::LOG_LEVEL::DEBUG, "log debug message");
        logger.log(Logger::LOG_LEVEL::INFO, "log info message");
        logger.log(Logger::LOG_LEVEL::WARNING, "log warning message");
        logger.log(Logger::LOG_LEVEL::ERROR, "log error message");
        logger.log(Logger::LOG_LEVEL::CRITICAL, "log critical message");

        logger.debug("debug message");
        logger.info("info message");
        logger.warning("warning message");
        logger.error("error message");
        logger.critical("critical message");

        TEST_ASSERT_EQUAL_STRING(
            "debug\n"
            "log debug message\n"
            "info\n"
            "log info message\n"
            "warning\n"
            "log warning message\n"
            "error\n"
            "log error message\n"
            "critical\n"
            "log critical message\n"
            "debug\n"
            "debug message\n"
            "info\n"
            "info message\n"
            "warning\n"
            "warning message\n"
            "error\n"
            "error message\n"
            "critical\n"
            "critical message\n",
            logger.getContent()
        );
    }

    void test_logging_chars() {
        char log_debug_message[] = "log debug message";
        char log_info_message[] = "log info message";
        char log_warning_message[] = "log warning message";
        char log_error_message[] = "log error message";
        char log_critical_message[] = "log critical message";

        char debug_message[] = "debug message";
        char info_message[] = "info message";
        char warning_message[] = "warning message";
        char error_message[] = "error message";
        char critical_message[] = "critical message";

        logger.log(Logger::LOG_LEVEL::DEBUG, log_debug_message);
        logger.log(Logger::LOG_LEVEL::INFO, log_info_message);
        logger.log(Logger::LOG_LEVEL::WARNING, log_warning_message);
        logger.log(Logger::LOG_LEVEL::ERROR, log_error_message);
        logger.log(Logger::LOG_LEVEL::CRITICAL, log_critical_message);

        logger.debug(debug_message);
        logger.info(info_message);
        logger.warning(warning_message);
        logger.error(error_message);
        logger.critical(critical_message);

        TEST_ASSERT_EQUAL_STRING(
            "debug\n"
            "log debug message\n"
            "info\n"
            "log info message\n"
            "warning\n"
            "log warning message\n"
            "error\n"
            "log error message\n"
            "critical\n"
            "log critical message\n"
            "debug\n"
            "debug message\n"
            "info\n"
            "info message\n"
            "warning\n"
            "warning message\n"
            "error\n"
            "error message\n"
            "critical\n"
            "critical message\n",
            logger.getContent()
        );
    }

    void test_logging_const_chars() {
        const char log_debug_message[] = "log debug message";
        const char log_info_message[] = "log info message";
        const char log_warning_message[] = "log warning message";
        const char log_error_message[] = "log error message";
        const char log_critical_message[] = "log critical message";

        const char debug_message[] = "debug message";
        const char info_message[] = "info message";
        const char warning_message[] = "warning message";
        const char error_message[] = "error message";
        const char critical_message[] = "critical message";

        logger.log(Logger::LOG_LEVEL::DEBUG, log_debug_message);
        logger.log(Logger::LOG_LEVEL::INFO, log_info_message);
        logger.log(Logger::LOG_LEVEL::WARNING, log_warning_message);
        logger.log(Logger::LOG_LEVEL::ERROR, log_error_message);
        logger.log(Logger::LOG_LEVEL::CRITICAL, log_critical_message);

        logger.debug(debug_message);
        logger.info(info_message);
        logger.warning(warning_message);
        logger.error(error_message);
        logger.critical(critical_message);

        TEST_ASSERT_EQUAL_STRING(
            "debug\n"
            "log debug message\n"
            "info\n"
            "log info message\n"
            "warning\n"
            "log warning message\n"
            "error\n"
            "log error message\n"
            "critical\n"
            "log critical message\n"
            "debug\n"
            "debug message\n"
            "info\n"
            "info message\n"
            "warning\n"
            "warning message\n"
            "error\n"
            "error message\n"
            "critical\n"
            "critical message\n",
            logger.getContent()
        );
    }

    void test_logging_unique_ptr_of_chars() {
        constexpr const auto f = DnApp::Common::Strings::makeUniquePtrOfChars;

        logger.log(Logger::LOG_LEVEL::DEBUG, f("log debug message"));
        logger.log(Logger::LOG_LEVEL::INFO, f("log info message"));
        logger.log(Logger::LOG_LEVEL::WARNING, f("log warning message"));
        logger.log(Logger::LOG_LEVEL::ERROR, f("log error message"));
        logger.log(Logger::LOG_LEVEL::CRITICAL, f("log critical message"));

        logger.debug(f("debug message"));
        logger.info(f("info message"));
        logger.warning(f("warning message"));
        logger.error(f("error message"));
        logger.critical(f("critical message"));

        TEST_ASSERT_EQUAL_STRING(
            "debug\n"
            "log debug message\n"
            "info\n"
            "log info message\n"
            "warning\n"
            "log warning message\n"
            "error\n"
            "log error message\n"
            "critical\n"
            "log critical message\n"
            "debug\n"
            "debug message\n"
            "info\n"
            "info message\n"
            "warning\n"
            "warning message\n"
            "error\n"
            "error message\n"
            "critical\n"
            "critical message\n",
            logger.getContent()
        );
    }
}

void setUp() {
    logger.clear();
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Logger);
    RUN_TEST(test_it_is_empty_at_start);
    RUN_TEST(test_clear);
    RUN_TEST(test_logging_literals);
    RUN_TEST(test_logging_chars);
    RUN_TEST(test_logging_const_chars);
    RUN_TEST(test_logging_unique_ptr_of_chars);

    return UNITY_END();
}
