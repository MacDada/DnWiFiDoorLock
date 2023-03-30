#include "unity.h"

#include "DnApp/Hardware/InMemoryButton.h"
#include "DnApp/Hardware/Button.h"
#include "DnApp/Unity/asserts.h"

namespace {
    auto button = DnApp::Hardware::InMemoryButton{};

    auto test_it_is_a_Button() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(DnApp::Hardware::Button, button);
    }

    auto test_it_was_not_pressed_at_start() -> void {
        TEST_ASSERT_EQUAL_INT(0, button.getPressCount());
    }

    auto test_pressing_increases_count() -> void {
        button.press();
        TEST_ASSERT_EQUAL_INT(1, button.getPressCount());

        button.press();
        TEST_ASSERT_EQUAL_INT(2, button.getPressCount());

        button.press();
        TEST_ASSERT_EQUAL_INT(3, button.getPressCount());
    }

    auto test_resetting_press_count() -> void {
        button.press();
        button.press();
        button.press();
        button.press();

        button.resetPressCount();

        TEST_ASSERT_EQUAL_INT(0, button.getPressCount());
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Button);
    RUN_TEST(test_it_was_not_pressed_at_start);
    RUN_TEST(test_pressing_increases_count);
    RUN_TEST(test_resetting_press_count);

    return UNITY_END();
}
