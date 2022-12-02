#include <unity.h>

void test_proof_of_concept() {
    TEST_ASSERT_TRUE(true);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_proof_of_concept);

    return UNITY_END();
}
