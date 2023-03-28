#include "unity.h"

#include "DnApp/Hardware/InMemoryDigitalPin.h"
#include "DnApp/Hardware/LedOnDigitalPin.h"
#include "DnApp/Hardware/Led.h"
#include "DnApp/Unity/asserts.h"

namespace {
    auto pin = DnApp::Hardware::InMemoryDigitalPin{};
    auto led = DnApp::Hardware::LedOnDigitalPin{pin};

    auto test_it_is_a_Led() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(DnApp::Hardware::Led, &led);
    }

    auto test_it_sets_output_mode_on_pin() -> void {
        TEST_ASSERT_TRUE(pin.isOutputMode());
    }

    auto test_it_is_off_by_default() -> void {
        TEST_ASSERT_TRUE(pin.isLow());

        TEST_ASSERT_TRUE(led.isOff());
        TEST_ASSERT_FALSE(led.isOn());
    }

    auto test_it_turns_on() -> void {
        led.on();

        TEST_ASSERT_TRUE(led.isOn());
        TEST_ASSERT_FALSE(led.isOff());

        TEST_ASSERT_TRUE(pin.isHigh());
    }

    auto test_it_turns_off() -> void {
        led.on();
        led.off();

        TEST_ASSERT_TRUE(led.isOff());
        TEST_ASSERT_FALSE(led.isOn());

        TEST_ASSERT_TRUE(pin.isLow());
    }

    auto test_toggle() -> void {
        led.toggle();
        TEST_ASSERT_TRUE(led.isOn());
        TEST_ASSERT_TRUE(pin.isHigh());

        led.toggle();
        TEST_ASSERT_TRUE(led.isOff());
        TEST_ASSERT_TRUE(pin.isLow());
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Led);
    RUN_TEST(test_it_sets_output_mode_on_pin);
    RUN_TEST(test_it_is_off_by_default);
    RUN_TEST(test_it_turns_on);
    RUN_TEST(test_it_turns_off);
    RUN_TEST(test_toggle);

    return UNITY_END();
}
