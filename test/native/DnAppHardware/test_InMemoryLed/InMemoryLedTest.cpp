#include "unity.h"

#include "DnApp/Hardware/InMemoryLed.h"
#include "DnApp/Hardware/Led.h"
#include "DnApp/Unity/asserts.h"

namespace {
    auto led = DnApp::Hardware::InMemoryLed{};

    void test_it_is_a_Led() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(DnApp::Hardware::Led, led);
    }

    void test_it_is_off_by_default() {
        TEST_ASSERT_TRUE(led.isOff());
        TEST_ASSERT_FALSE(led.isOn());
    }

    void test_it_turns_on() {
        led.on();

        TEST_ASSERT_TRUE(led.isOn());
        TEST_ASSERT_FALSE(led.isOff());
    }

    void test_it_turns_off() {
        led.on();
        led.off();

        TEST_ASSERT_TRUE(led.isOff());
        TEST_ASSERT_FALSE(led.isOn());
    }

    void test_toggle() {
        led.toggle();
        TEST_ASSERT_TRUE(led.isOn());

        led.toggle();
        TEST_ASSERT_TRUE(led.isOff());
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Led);
    RUN_TEST(test_it_is_off_by_default);
    RUN_TEST(test_it_turns_on);
    RUN_TEST(test_it_turns_off);
    RUN_TEST(test_toggle);

    return UNITY_END();
}
