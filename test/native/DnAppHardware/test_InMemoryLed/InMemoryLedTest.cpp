#include "unity.h"

#include "DnApp/Hardware/InMemoryLed.h"

namespace {
    DnApp::Hardware::InMemoryLed led{};

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

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_off_by_default);
    RUN_TEST(test_it_turns_on);
    RUN_TEST(test_it_turns_off);
    RUN_TEST(test_toggle);

    return UNITY_END();
}
