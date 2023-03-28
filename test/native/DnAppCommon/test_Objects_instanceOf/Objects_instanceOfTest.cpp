#include <unity.h>

#include "DnApp/Common/Objects.h"

namespace {
    using DnApp::Common::Objects::instanceOf;

    class Parent {
    };

    class OtherParent {
    };

    class Child: public Parent, OtherParent {
    };

    class GrandChild: public Child {
    };

    auto parent = Parent{};

    auto otherParent = OtherParent{};

    auto child = Child{};

    auto grandChild = GrandChild{};

    auto test_instance_of_itself() -> void {
        TEST_ASSERT_TRUE(instanceOf<Parent>(&parent));
        TEST_ASSERT_TRUE(instanceOf<OtherParent>(&otherParent));
        TEST_ASSERT_TRUE(instanceOf<Child>(&child));
        TEST_ASSERT_TRUE(instanceOf<GrandChild>(&grandChild));
    }

    auto test_child_is_instance_of_parents() -> void {
        TEST_ASSERT_TRUE(instanceOf<Parent>(&child));
        TEST_ASSERT_TRUE(instanceOf<OtherParent>(&child));
    }

    auto test_grandchild_is_instance_of_child_and_parents() -> void {
        TEST_ASSERT_TRUE(instanceOf<Parent>(&grandChild));
        TEST_ASSERT_TRUE(instanceOf<OtherParent>(&grandChild));
        TEST_ASSERT_TRUE(instanceOf<Child>(&grandChild));
    }

    auto test_parent_is_not_instance_of_other_parent() -> void {
        TEST_ASSERT_FALSE(instanceOf<Parent>(&otherParent));
        TEST_ASSERT_FALSE(instanceOf<OtherParent>(&parent));
    }

    auto test_parent_is_not_instance_of_child_and_grandchild() -> void {
        TEST_ASSERT_FALSE(instanceOf<Child>(&parent));
        TEST_ASSERT_FALSE(instanceOf<GrandChild>(&parent));
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(test_instance_of_itself);
    RUN_TEST(test_child_is_instance_of_parents);
    RUN_TEST(test_grandchild_is_instance_of_child_and_parents);
    RUN_TEST(test_parent_is_not_instance_of_other_parent);
    RUN_TEST(test_parent_is_not_instance_of_child_and_grandchild);

    return UNITY_END();
}
