#include "unity.h"

#include "DnApp/Common/Strings.h"

namespace {
    using DnApp::Common::Strings::format;

    auto test_format_empty_string() -> void {
        TEST_ASSERT_EQUAL_STRING(
            "",
            format("").get()
        );
    }

    auto test_format_a_string() -> void {
        TEST_ASSERT_EQUAL_STRING(
            "FooBarBaz",
            format("FooBarBaz").get()
        );
    }

    auto test_format_with_string_interpolation() -> void {
        TEST_ASSERT_EQUAL_STRING(
            "Foo Bar",
            format("Foo %s", "Bar").get()
        );
    }

    auto test_format_with_mixed_interpolation() -> void {
        TEST_ASSERT_EQUAL_STRING(
            "Hello Baz World 23!",
            format("Hello %s World %d!", "Baz", 23).get()
        );
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_format_empty_string);
    RUN_TEST(test_format_a_string);
    RUN_TEST(test_format_with_string_interpolation);
    RUN_TEST(test_format_with_mixed_interpolation);

    return UNITY_END();
}
