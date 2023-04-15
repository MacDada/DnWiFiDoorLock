#include "unity.h"

#include "DnApp/Hardware/Servo.h"

namespace {
    using Angle = DnApp::Hardware::Servo::Angle;

    auto test_it_returns_Angle_for_valid_degrees() -> void {
        const auto angle = Angle::withDegrees(17);

        TEST_ASSERT_TRUE(angle.has_value());
        TEST_ASSERT_EQUAL_INT(17, angle->getDegrees());
    }

    auto test_it_returns_Angle_for_MIN_degrees() -> void {
        const auto angle = Angle::withDegrees(Angle::MIN);

        TEST_ASSERT_TRUE(angle.has_value());
        TEST_ASSERT_EQUAL_INT(Angle::MIN, angle->getDegrees());
    }

    auto test_it_returns_Angle_for_MAX_degrees() -> void {
        const auto angle = Angle::withDegrees(Angle::MAX);

        TEST_ASSERT_TRUE(angle.has_value());
        TEST_ASSERT_EQUAL_INT(Angle::MAX, angle->getDegrees());
    }

    auto test_it_returns_no_value_for_too_small_degrees() -> void {
        const auto angle = Angle::withDegrees(Angle::MIN - 1);

        TEST_ASSERT_FALSE(angle.has_value());
    }

    auto test_it_returns_no_value_for_too_high_degrees() -> void {
        const auto angle = Angle::withDegrees(Angle::MAX + 1);

        TEST_ASSERT_FALSE(angle.has_value());
    }

    auto test_copying() -> void {
        const auto angle = Angle::withDegrees(120);
        const auto angle2 = angle;

        TEST_ASSERT_EQUAL_INT(120, angle2->getDegrees());
    }

    auto test_angles_with_equal_degrees_are_equal() -> void {
        const auto angle1 = Angle::withDegrees(12).value();
        const auto angle2 = Angle::withDegrees(12).value();

        TEST_ASSERT_TRUE(angle1 == angle2);
    }

    auto test_angles_with_different_degrees_are_not_equal() -> void {
        const auto angle1 = Angle::withDegrees(12).value();
        const auto angle2 = Angle::withDegrees(13).value();

        TEST_ASSERT_TRUE(angle1 != angle2);
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_it_returns_Angle_for_valid_degrees);
    RUN_TEST(test_it_returns_Angle_for_MIN_degrees);
    RUN_TEST(test_it_returns_Angle_for_MAX_degrees);
    RUN_TEST(test_it_returns_no_value_for_too_small_degrees);
    RUN_TEST(test_it_returns_no_value_for_too_high_degrees);
    RUN_TEST(test_copying);
    RUN_TEST(test_angles_with_equal_degrees_are_equal);
    RUN_TEST(test_angles_with_different_degrees_are_not_equal);

    return UNITY_END();
}
