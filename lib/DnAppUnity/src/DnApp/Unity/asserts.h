#pragma once

#include <unity.h>

#include "DnApp/Common/Objects.h"

#define DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(expectedClass, actualObject)        \
    UNITY_TEST_ASSERT(                                                           \
        (DnApp::Common::Objects::instanceOf<expectedClass>(&actualObject)),       \
        __LINE__,                                                                \
        "Expected `" #actualObject "` to be an instance of `" #expectedClass "`" \
    )

#define DN_APP_UNITY_TEST_ASSERT_NOT_INSTANCE_OF(expectedClass, actualObject)        \
    UNITY_TEST_ASSERT(                                                               \
        !(DnApp::Common::Objects::instanceOf<expectedClass>(&actualObject)),          \
        __LINE__,                                                                    \
        "Expected `" #actualObject "` not to be an instance of `" #expectedClass "`" \
    )
