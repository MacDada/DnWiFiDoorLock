#include "unity.h"

#include "DnApp/Hardware/DigitalPin.h"
#include "DnApp/Hardware/DigitalPinLevelInverter.h"
#include "DnApp/Hardware/InMemoryDigitalPin.h"
#include "DnApp/Unity/asserts.h"

namespace {
    auto pin = DnApp::Hardware::InMemoryDigitalPin{};
    auto inverter = DnApp::Hardware::DigitalPinLevelInverter{pin};

    auto test_it_is_a_DigitalPin() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(DnApp::Hardware::DigitalPin, &inverter);
    }

    auto test_output_mode_is_normal() -> void {
        inverter.setOutputMode();
        TEST_ASSERT_TRUE(pin.isOutputMode());

        inverter.setInputMode();
        TEST_ASSERT_TRUE(pin.isInputMode());
    }

    auto test_levels_are_inverted_by_default() -> void {
        TEST_ASSERT_EQUAL(pin.isHigh(), inverter.isLow());
        TEST_ASSERT_EQUAL(pin.isLow(), inverter.isHigh());
    }

    auto test_setting_high_is_inverted() -> void {
        pin.setLow();

        inverter.setLow();

        TEST_ASSERT_TRUE(inverter.isLow());
        TEST_ASSERT_FALSE(inverter.isHigh());

        TEST_ASSERT_TRUE(pin.isHigh());
        TEST_ASSERT_FALSE(pin.isLow());
    }

    auto test_setting_low_is_inverted() -> void {
        pin.setHigh();

        inverter.setHigh();

        TEST_ASSERT_TRUE(inverter.isHigh());
        TEST_ASSERT_FALSE(inverter.isLow());

        TEST_ASSERT_TRUE(pin.isLow());
        TEST_ASSERT_FALSE(pin.isHigh());
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_DigitalPin);
    RUN_TEST(test_output_mode_is_normal);
    RUN_TEST(test_levels_are_inverted_by_default);
    RUN_TEST(test_setting_high_is_inverted);
    RUN_TEST(test_setting_low_is_inverted);

    return UNITY_END();
}
