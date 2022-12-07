#include <Arduino.h>
#include <unity.h>

namespace {
    void test_proof_of_concept() {
        TEST_ASSERT_EQUAL_INT(13, LED_BUILTIN);
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_proof_of_concept);

    return UNITY_END();
}
