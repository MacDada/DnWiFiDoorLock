#include <Arduino.h>
#include <unity.h>

namespace {
    auto test_proof_of_concept() -> void {
        TEST_ASSERT_EQUAL_INT(13, LED_BUILTIN);
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_proof_of_concept);

    return UNITY_END();
}
