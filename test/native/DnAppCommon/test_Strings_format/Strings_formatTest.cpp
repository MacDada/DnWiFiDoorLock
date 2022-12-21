#include "unity.h"

#include "DnApp/Common/Strings.h"

namespace {
    using DnApp::Common::Strings::format;

    void test_format_empty_string() {
        TEST_ASSERT_EQUAL_STRING(
            "",
            format("").get()
        );
    }

    void test_format_a_string() {
        TEST_ASSERT_EQUAL_STRING(
            "FooBarBaz",
            format("FooBarBaz").get()
        );
    }

    void test_format_with_string_interpolation() {
        TEST_ASSERT_EQUAL_STRING(
            "Foo Bar",
            format("Foo %s", "Bar").get()
        );
    }

    void test_format_with_mixed_interpolation() {
        TEST_ASSERT_EQUAL_STRING(
            "Hello Baz World 23!",
            format("Hello %s World %d!", "Baz", 23).get()
        );
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_format_empty_string);
    RUN_TEST(test_format_a_string);
    RUN_TEST(test_format_with_string_interpolation);
    RUN_TEST(test_format_with_mixed_interpolation);

    return UNITY_END();
}
