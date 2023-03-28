#include <unity.h>

#include "DnApp/Unity/asserts.h"

namespace {
    class Parent {
    };

    class OtherParent {
    };

    class Child:
        public Parent, OtherParent {
    };

    class GrandChild:
        public Child {
    };

    auto parent = Parent{};

    auto otherParent = OtherParent{};

    auto child = Child{};

    auto grandChild = GrandChild{};

    auto test_instance_of_itself() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Parent, &parent);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(OtherParent, &otherParent);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Child, &child);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(GrandChild, &grandChild);
    }

    auto test_child_is_instance_of_parents() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Parent, &child);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(OtherParent, &child);
    }

    auto test_grandchild_is_instance_of_child_and_parents() -> void {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Parent, &grandChild);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(OtherParent, &grandChild);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Child, &grandChild);
    }

    auto test_parent_is_not_instance_of_other_parent() -> void {
        DN_APP_UNITY_TEST_ASSERT_NOT_INSTANCE_OF(Parent, &otherParent);
        DN_APP_UNITY_TEST_ASSERT_NOT_INSTANCE_OF(OtherParent, &parent);
    }

    auto test_parent_is_not_instance_of_child_and_grandchild() -> void {
        DN_APP_UNITY_TEST_ASSERT_NOT_INSTANCE_OF(Child, &parent);
        DN_APP_UNITY_TEST_ASSERT_NOT_INSTANCE_OF(GrandChild, &parent);
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
