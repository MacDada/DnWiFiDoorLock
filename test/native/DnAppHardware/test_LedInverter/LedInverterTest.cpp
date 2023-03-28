#include "unity.h"

#include "DnApp/Hardware/InMemoryLed.h"
#include "DnApp/Hardware/LedInverter.h"
#include "DnApp/Hardware/Led.h"
#include "DnApp/Unity/asserts.h"

namespace {
    auto led = DnApp::Hardware::InMemoryLed{};
    auto inverter = DnApp::Hardware::LedInverter{led};

    auto test_it_is_a_Led() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(DnApp::Hardware::Led, &inverter);
    }

    auto test_it_is_inverted_by_default() -> void {
        TEST_ASSERT_EQUAL(led.isOn(), inverter.isOff());
        TEST_ASSERT_EQUAL(led.isOff(), inverter.isOn());
    }

    auto test_is_on_is_inverted() -> void {
        led.on();

        TEST_ASSERT_TRUE(inverter.isOff());
        TEST_ASSERT_FALSE(inverter.isOn());
    }

    auto test_is_off_is_inverted() -> void {
        led.off();

        TEST_ASSERT_TRUE(inverter.isOn());
        TEST_ASSERT_FALSE(inverter.isOff());
    }

    auto test_turning_on_is_inverted() -> void {
        led.on();

        inverter.on();

        TEST_ASSERT_TRUE(led.isOff());
        TEST_ASSERT_TRUE(inverter.isOn());
        TEST_ASSERT_FALSE(inverter.isOff());
    }

    auto test_turning_off_is_inverted() -> void {
        led.off();

        inverter.off();

        TEST_ASSERT_TRUE(led.isOn());
        TEST_ASSERT_TRUE(inverter.isOff());
        TEST_ASSERT_FALSE(inverter.isOn());
    }

    auto test_toggle_from_off_is_inverted() -> void {
        inverter.off();

        inverter.toggle();

        TEST_ASSERT_TRUE(inverter.isOn());
        TEST_ASSERT_FALSE(inverter.isOff());

        TEST_ASSERT_FALSE(led.isOn());
        TEST_ASSERT_TRUE(led.isOff());
    }

    auto test_toggle_from_on_is_inverted() -> void {
        inverter.on();

        inverter.toggle();

        TEST_ASSERT_TRUE(inverter.isOff());
        TEST_ASSERT_FALSE(inverter.isOn());

        TEST_ASSERT_FALSE(led.isOff());
        TEST_ASSERT_TRUE(led.isOn());
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Led);
    RUN_TEST(test_it_is_inverted_by_default);
    RUN_TEST(test_is_on_is_inverted);
    RUN_TEST(test_is_off_is_inverted);
    RUN_TEST(test_turning_on_is_inverted);
    RUN_TEST(test_turning_off_is_inverted);
    RUN_TEST(test_toggle_from_off_is_inverted);
    RUN_TEST(test_toggle_from_on_is_inverted);

    return UNITY_END();
}
