#include <unity.h>

#include "DnApp/Logger/NullLogger.h"

#include "../LoggerTest.h"

namespace {
    DnApp::Logger::NullLogger nullLogger;
}

namespace DnApp::Logger::LoggerTest {
    DnApp::Logger::Logger &logger = nullLogger;

    void run_tests() {
        RUN_TEST(test_it_is_a_Logger);
        RUN_TEST(test_logging_chars);
        RUN_TEST(test_logging_const_chars);
        RUN_TEST(test_logging_unique_ptr_of_chars);
    }
}

int main() {
    UNITY_BEGIN();

    DnApp::Logger::LoggerTest::run_tests();

    return UNITY_END();
}
