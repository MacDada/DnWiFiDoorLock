#include "unity.h"

#include "DnApp/Hardware/InMemoryDigitalPin.h"
#include "DnApp/Hardware/LedOnDigitalPin.h"
#include "DnApp/Hardware/Led.h"
#include "DnApp/Unity/asserts.h"

namespace {
    DnApp::Hardware::InMemoryDigitalPin pin{};
    DnApp::Hardware::LedOnDigitalPin led{pin};

    void test_it_is_a_Led() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(DnApp::Hardware::Led, &led);
    }

    void test_it_sets_output_mode_on_pin() {
        TEST_ASSERT_TRUE(pin.isOutputMode());
    }

    void test_it_is_off_by_default() {
        TEST_ASSERT_TRUE(pin.isLow());

        TEST_ASSERT_TRUE(led.isOff());
        TEST_ASSERT_FALSE(led.isOn());
    }

    void test_it_turns_on() {
        led.on();

        TEST_ASSERT_TRUE(led.isOn());
        TEST_ASSERT_FALSE(led.isOff());

        TEST_ASSERT_TRUE(pin.isHigh());
    }

    void test_it_turns_off() {
        led.on();
        led.off();

        TEST_ASSERT_TRUE(led.isOff());
        TEST_ASSERT_FALSE(led.isOn());

        TEST_ASSERT_TRUE(pin.isLow());
    }

    void test_toggle() {
        led.toggle();
        TEST_ASSERT_TRUE(led.isOn());
        TEST_ASSERT_TRUE(pin.isHigh());

        led.toggle();
        TEST_ASSERT_TRUE(led.isOff());
        TEST_ASSERT_TRUE(pin.isLow());
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Led);
    RUN_TEST(test_it_sets_output_mode_on_pin);
    RUN_TEST(test_it_is_off_by_default);
    RUN_TEST(test_it_turns_on);
    RUN_TEST(test_it_turns_off);
    RUN_TEST(test_toggle);

    return UNITY_END();
}
