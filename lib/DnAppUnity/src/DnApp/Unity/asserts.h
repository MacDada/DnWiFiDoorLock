#pragma once

#include <unity.h>

#include "DnApp/Unity/functions.h"

namespace DnApp::Unity {
    template<typename ExpectedBaseClass, typename ObjectClass>
    inline void TEST_ASSERT_INSTANCE_OF(const ObjectClass *object) {
        TEST_ASSERT_TRUE(instance_of<ExpectedBaseClass>(object));
    }

    template<typename ExpectedBaseClass, typename ObjectClass>
    inline void TEST_ASSERT_NOT_INSTANCE_OF(const ObjectClass *object) {
        TEST_ASSERT_FALSE(instance_of<ExpectedBaseClass>(object));
    }
}
