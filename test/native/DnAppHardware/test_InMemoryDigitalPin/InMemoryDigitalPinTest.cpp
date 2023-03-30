#include "unity.h"

#include "DnApp/Hardware/DigitalPin.h"
#include "DnApp/Hardware/InMemoryDigitalPin.h"
#include "DnApp/Unity/asserts.h"

namespace {
    auto pin = DnApp::Hardware::InMemoryDigitalPin{};

    void test_it_is_a_DigitalPin() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(DnApp::Hardware::DigitalPin, pin);
    }

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

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_DigitalPin);
    RUN_TEST(test_it_is_low_by_default);
    RUN_TEST(test_setting_level);
    RUN_TEST(test_it_is_input_mode_by_default);
    RUN_TEST(test_setting_mode);

    return UNITY_END();
}
