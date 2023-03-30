#include <WString.h>
#include <unity.h>

#include "DnApp/Arduino/functions.h"
#include "DnApp/Unity/asserts.h"

namespace {
    using DnApp::Arduino::functions::dataToString;

    auto testEmptyReturnsEmpty() -> void {
        const uint8_t given[] = "";

        const auto actual = dataToString(given, 0);

        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(String, &actual);
        TEST_ASSERT_EQUAL_STRING("", actual.c_str());
    }

    auto testStringWithNoLengthReturnsEmpty() -> void {
        const uint8_t given[] = "foo";

        const auto actual = dataToString(given, 0);

        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(String, &actual);
        TEST_ASSERT_EQUAL_STRING("", actual.c_str());
    }

    auto testALetter() -> void {
        const uint8_t given[] = "f";

        const auto actual = dataToString(given, 1);

        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(String, &actual);
        TEST_ASSERT_EQUAL_STRING("f", actual.c_str());
    }

    auto testAString() -> void {
        const uint8_t given[] = "foo bar";

        const auto actual = dataToString(given, 7);

        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(String, &actual);
        TEST_ASSERT_EQUAL_STRING("foo bar", actual.c_str());
    }

    auto testAShorterLengthCanBeGiven() -> void {
        const uint8_t given[] = "bar";

        const auto actual = dataToString(given, 2);

        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(String, &actual);
        TEST_ASSERT_EQUAL_STRING("ba", actual.c_str());
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(testEmptyReturnsEmpty);
    RUN_TEST(testStringWithNoLengthReturnsEmpty);
    RUN_TEST(testALetter);
    RUN_TEST(testAString);
    RUN_TEST(testAShorterLengthCanBeGiven);

    return UNITY_END();
}
