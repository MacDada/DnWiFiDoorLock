#include <unity.h>

#include "DnApp/Common/ElapsedTime.h"

namespace {
    using DnApp::Common::ElapsedTime;

    auto testMinimal() -> void {
        const auto time = ElapsedTime{0};

        TEST_ASSERT_EQUAL_INT(0, time.getDays());
        TEST_ASSERT_EQUAL_INT(0, time.getHours());
        TEST_ASSERT_EQUAL_INT(0, time.getMinutes());
        TEST_ASSERT_EQUAL_INT(0, time.getSeconds());
        TEST_ASSERT_EQUAL_INT(0, time.getMilliseconds());

        TEST_ASSERT_EQUAL_INT(0, time.getRemainingHours());
        TEST_ASSERT_EQUAL_INT(0, time.getRemainingMinutes());
        TEST_ASSERT_EQUAL_INT(0, time.getRemainingSeconds());
        TEST_ASSERT_EQUAL_INT(0, time.getRemainingMilliseconds());
    }

    auto testTypical() -> void {
        const auto sevenDaysAndABitMore = 634567224;
        const auto time = ElapsedTime{sevenDaysAndABitMore};

        TEST_ASSERT_EQUAL_INT(7, time.getDays());
        TEST_ASSERT_EQUAL_INT(176, time.getHours());
        TEST_ASSERT_EQUAL_INT(10576, time.getMinutes());
        TEST_ASSERT_EQUAL_INT(634567, time.getSeconds());
        TEST_ASSERT_EQUAL_INT(634567224, time.getMilliseconds());

        TEST_ASSERT_EQUAL_INT(8, time.getRemainingHours());
        TEST_ASSERT_EQUAL_INT(16, time.getRemainingMinutes());
        TEST_ASSERT_EQUAL_INT(7, time.getRemainingSeconds());
        TEST_ASSERT_EQUAL_INT(224, time.getRemainingMilliseconds());
    }

    auto testMaximal() -> void {
        const auto time = ElapsedTime{4294967295};

        TEST_ASSERT_EQUAL_INT(49, time.getDays());
        TEST_ASSERT_EQUAL_INT(1193, time.getHours());
        TEST_ASSERT_EQUAL_INT(71582, time.getMinutes());
        TEST_ASSERT_EQUAL_INT(4294967, time.getSeconds());
        TEST_ASSERT_EQUAL_INT(4294967295, time.getMilliseconds());

        TEST_ASSERT_EQUAL_INT(17, time.getRemainingHours());
        TEST_ASSERT_EQUAL_INT(2, time.getRemainingMinutes());
        TEST_ASSERT_EQUAL_INT(47, time.getRemainingSeconds());
        TEST_ASSERT_EQUAL_INT(295, time.getRemainingMilliseconds());
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(testMinimal);
    RUN_TEST(testTypical);
    RUN_TEST(testMaximal);

    return UNITY_END();
}
