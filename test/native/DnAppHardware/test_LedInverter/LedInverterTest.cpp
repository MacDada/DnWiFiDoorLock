#include "unity.h"

#include "DnApp/Hardware/InMemoryLed.h"
#include "DnApp/Hardware/LedInverter.h"
#include "DnApp/Hardware/Led.h"
#include "DnApp/Unity/asserts.h"

namespace {
    DnApp::Hardware::InMemoryLed led{};
    DnApp::Hardware::LedInverter inverter{led};

    void test_it_is_a_Led() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(DnApp::Hardware::Led, &inverter);
    }

    void test_it_is_inverted_by_default() {
        TEST_ASSERT_EQUAL(led.isOn(), inverter.isOff());
        TEST_ASSERT_EQUAL(led.isOff(), inverter.isOn());
    }

    void test_is_on_is_inverted() {
        led.on();

        TEST_ASSERT_TRUE(inverter.isOff());
        TEST_ASSERT_FALSE(inverter.isOn());
    }

    void test_is_off_is_inverted() {
        led.off();

        TEST_ASSERT_TRUE(inverter.isOn());
        TEST_ASSERT_FALSE(inverter.isOff());
    }

    void test_turning_on_is_inverted() {
        led.on();

        inverter.on();

        TEST_ASSERT_TRUE(led.isOff());
        TEST_ASSERT_TRUE(inverter.isOn());
        TEST_ASSERT_FALSE(inverter.isOff());
    }

    void test_turning_off_is_inverted() {
        led.off();

        inverter.off();

        TEST_ASSERT_TRUE(led.isOn());
        TEST_ASSERT_TRUE(inverter.isOff());
        TEST_ASSERT_FALSE(inverter.isOn());
    }

    void test_toggle_from_off_is_inverted() {
        inverter.off();

        inverter.toggle();

        TEST_ASSERT_TRUE(inverter.isOn());
        TEST_ASSERT_FALSE(inverter.isOff());

        TEST_ASSERT_FALSE(led.isOn());
        TEST_ASSERT_TRUE(led.isOff());
    }

    void test_toggle_from_on_is_inverted() {
        inverter.on();

        inverter.toggle();

        TEST_ASSERT_TRUE(inverter.isOff());
        TEST_ASSERT_FALSE(inverter.isOn());

        TEST_ASSERT_FALSE(led.isOff());
        TEST_ASSERT_TRUE(led.isOn());
    }
}

int main() {
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
