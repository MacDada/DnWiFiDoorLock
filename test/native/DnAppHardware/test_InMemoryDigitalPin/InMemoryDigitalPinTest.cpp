#include "unity.h"

#include "DnApp/Hardware/InMemoryDigitalPin.h"

namespace {
    DnApp::Hardware::InMemoryDigitalPin pin{};

    void test_it_is_low_by_default() {
        TEST_ASSERT_TRUE(pin.isLow());
        TEST_ASSERT_FALSE(pin.isHigh());
    }

    void test_setting_level() {
        pin.setHigh();

        TEST_ASSERT_TRUE(pin.isHigh());
        TEST_ASSERT_FALSE(pin.isLow());

        pin.setLow();
        TEST_ASSERT_TRUE(pin.isLow());
        TEST_ASSERT_FALSE(pin.isHigh());
    }

    void test_it_is_input_mode_by_default() {
        TEST_ASSERT_TRUE(pin.isInputMode());
        TEST_ASSERT_FALSE(pin.isOutputMode());
    }

    void test_setting_mode() {
        pin.setOutputMode();

        TEST_ASSERT_TRUE(pin.isOutputMode());
        TEST_ASSERT_FALSE(pin.isInputMode());

        pin.setInputMode();

        TEST_ASSERT_TRUE(pin.isInputMode());
        TEST_ASSERT_FALSE(pin.isOutputMode());
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_low_by_default);
    RUN_TEST(test_setting_level);
    RUN_TEST(test_it_is_input_mode_by_default);
    RUN_TEST(test_setting_mode);

    return UNITY_END();
}
