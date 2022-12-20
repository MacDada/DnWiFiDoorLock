#include "unity.h"

#include "DnApp/Common/Strings.h"

namespace {
    void test_making_unique_ptr_of_chars() {
        TEST_ASSERT_EQUAL_STRING(
            "FooBarBaz",
            DnApp::Common::Strings::makeUniquePtrOfChars("FooBarBaz").get()
        );
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_making_unique_ptr_of_chars);

    return UNITY_END();
}