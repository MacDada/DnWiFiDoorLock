#include "unity.h"

#include "DnApp/Common/Strings.h"

namespace {
    auto test_making_unique_ptr_of_chars() -> void {
        TEST_ASSERT_EQUAL_STRING(
            "FooBarBaz",
            DnApp::Common::Strings::makeUniquePtrOfChars("FooBarBaz").get()
        );
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_making_unique_ptr_of_chars);

    return UNITY_END();
}
