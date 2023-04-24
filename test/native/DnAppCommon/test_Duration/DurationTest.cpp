#include <unity.h>

#include "DnApp/Common/Duration.h"

namespace {
    using DnApp::Common::Duration;

    auto testMinimal() -> void {
        const auto duration = Duration{0};

        TEST_ASSERT_EQUAL_INT(0, duration.getDays());
        TEST_ASSERT_EQUAL_INT(0, duration.getHours());
        TEST_ASSERT_EQUAL_INT(0, duration.getMinutes());
        TEST_ASSERT_EQUAL_INT(0, duration.getSeconds());
        TEST_ASSERT_EQUAL_INT(0, duration.getMilliseconds());

        TEST_ASSERT_EQUAL_INT(0, duration.getHoursRemainder());
        TEST_ASSERT_EQUAL_INT(0, duration.getMinutesRemainder());
        TEST_ASSERT_EQUAL_INT(0, duration.getSecondsRemainder());
        TEST_ASSERT_EQUAL_INT(0, duration.getMillisecondsRemainder());
    }

    auto testTypical() -> void {
        const auto sevenDaysAndABitMore = 634567224;
        const auto duration = Duration{sevenDaysAndABitMore};

        TEST_ASSERT_EQUAL_INT(7, duration.getDays());
        TEST_ASSERT_EQUAL_INT(176, duration.getHours());
        TEST_ASSERT_EQUAL_INT(10576, duration.getMinutes());
        TEST_ASSERT_EQUAL_INT(634567, duration.getSeconds());
        TEST_ASSERT_EQUAL_INT(634567224, duration.getMilliseconds());

        TEST_ASSERT_EQUAL_INT(8, duration.getHoursRemainder());
        TEST_ASSERT_EQUAL_INT(16, duration.getMinutesRemainder());
        TEST_ASSERT_EQUAL_INT(7, duration.getSecondsRemainder());
        TEST_ASSERT_EQUAL_INT(224, duration.getMillisecondsRemainder());
    }

    auto testMaximal() -> void {
        const auto duration = Duration{4294967295};

        TEST_ASSERT_EQUAL_INT(49, duration.getDays());
        TEST_ASSERT_EQUAL_INT(1193, duration.getHours());
        TEST_ASSERT_EQUAL_INT(71582, duration.getMinutes());
        TEST_ASSERT_EQUAL_INT(4294967, duration.getSeconds());
        TEST_ASSERT_EQUAL_INT(4294967295, duration.getMilliseconds());

        TEST_ASSERT_EQUAL_INT(17, duration.getHoursRemainder());
        TEST_ASSERT_EQUAL_INT(2, duration.getMinutesRemainder());
        TEST_ASSERT_EQUAL_INT(47, duration.getSecondsRemainder());
        TEST_ASSERT_EQUAL_INT(295, duration.getMillisecondsRemainder());
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(testMinimal);
    RUN_TEST(testTypical);
    RUN_TEST(testMaximal);

    return UNITY_END();
}
