#include "unity.h"

#include "DnApp/Hardware/InMemoryServo.h"
#include "DnApp/Hardware/Servo.h"
#include "DnApp/Unity/asserts.h"

namespace {
    auto servo = DnApp::Hardware::InMemoryServo{};

    auto test_it_is_a_Servo() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(DnApp::Hardware::Servo, servo);
    }

    auto test_angle_is_zero_by_default() -> void {
        TEST_ASSERT_EQUAL_INT(0, servo.getAngle().getDegrees());
    }

    auto test_setting_angle() -> void {
        servo.setAngle(DnApp::Hardware::Servo::Angle::withDegrees(12).value());

        TEST_ASSERT_EQUAL_INT(12, servo.getAngle().getDegrees());
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_is_a_Servo);
    RUN_TEST(test_angle_is_zero_by_default);
    RUN_TEST(test_setting_angle);

    return UNITY_END();
}
