#include "unity.h"

#include "DnApp/Hardware/InMemoryDigitalPin.h"
#include "DnApp/Hardware/DigitalPinLevelInverter.h"

namespace {
    DnApp::Hardware::InMemoryDigitalPin pin{};
    DnApp::Hardware::DigitalPinLevelInverter inverter{pin};

    void test_output_mode_is_normal() {
        inverter.setOutputMode();
        TEST_ASSERT_TRUE(pin.isOutputMode());

        inverter.setInputMode();
        TEST_ASSERT_TRUE(pin.isInputMode());
    }

    void test_levels_are_inverted_by_default() {
        TEST_ASSERT_EQUAL(pin.isHigh(), inverter.isLow());
        TEST_ASSERT_EQUAL(pin.isLow(), inverter.isHigh());
    }

    void test_setting_high_is_inverted() {
        pin.setLow();

        inverter.setLow();

        TEST_ASSERT_TRUE(inverter.isLow());
        TEST_ASSERT_FALSE(inverter.isHigh());

        TEST_ASSERT_TRUE(pin.isHigh());
        TEST_ASSERT_FALSE(pin.isLow());
    }

    void test_setting_low_is_inverted() {
        pin.setHigh();

        inverter.setHigh();

        TEST_ASSERT_TRUE(inverter.isHigh());
        TEST_ASSERT_FALSE(inverter.isLow());

        TEST_ASSERT_TRUE(pin.isLow());
        TEST_ASSERT_FALSE(pin.isHigh());
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_output_mode_is_normal);
    RUN_TEST(test_levels_are_inverted_by_default);
    RUN_TEST(test_setting_high_is_inverted);
    RUN_TEST(test_setting_low_is_inverted);

    return UNITY_END();
}
