#include "unity.h"

#include "DnApp/Hardware/InMemoryButton.h"
#include "DnApp/Hardware/Button.h"
#include "DnApp/Unity/asserts.h"

namespace {
    DnApp::Hardware::InMemoryButton button{};

    void test_it_is_a_Button() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(DnApp::Hardware::Button, &button);
    }

    void test_it_was_not_pressed_at_start() {
        TEST_ASSERT_EQUAL_INT(0, button.getPressCount());
    }

    void test_pressing_increases_count() {
        button.press();
        TEST_ASSERT_EQUAL_INT(1, button.getPressCount());

        button.press();
        TEST_ASSERT_EQUAL_INT(2, button.getPressCount());

        button.press();
        TEST_ASSERT_EQUAL_INT(3, button.getPressCount());
    }

    void test_resetting_press_count() {
        button.press();
        button.press();
        button.press();
        button.press();

        button.resetPressCount();

        TEST_ASSERT_EQUAL_INT(0, button.getPressCount());
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Button);
    RUN_TEST(test_it_was_not_pressed_at_start);
    RUN_TEST(test_pressing_increases_count);
    RUN_TEST(test_resetting_press_count);

    return UNITY_END();
}
