#pragma once

#include <unity.h>

#include "DnApp/Unity/functions.h"

#define TEST_ASSERT_INSTANCE_OF(expectedClass, actualObject)                     \
    UNITY_TEST_ASSERT(                                                           \
        (DnApp::Unity::instance_of<expectedClass>(actualObject)),                \
        __LINE__,                                                                \
        "Expected `" #actualObject "` to be an instance of `" #expectedClass "`" \
    )

#define TEST_ASSERT_NOT_INSTANCE_OF(expectedClass, actualObject)                     \
    UNITY_TEST_ASSERT(                                                               \
        !(DnApp::Unity::instance_of<expectedClass>(actualObject)),                   \
        __LINE__,                                                                    \
        "Expected `" #actualObject "` not to be an instance of `" #expectedClass "`" \
    )
