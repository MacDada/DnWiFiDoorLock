#include <unity.h>

#include "DnApp/Unity/asserts.h"

namespace {
    class Parent {
    } parent;

    class OtherParent {
    } otherParent;

    class Child: public Parent, OtherParent {
    } child;

    class GrandChild: public Child {
    } grandChild;

    void test_instance_of_itself() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Parent, &parent);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(OtherParent, &otherParent);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Child, &child);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(GrandChild, &grandChild);
    }

    void test_child_is_instance_of_parents() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Parent, &child);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(OtherParent, &child);
    }

    void test_grandchild_is_instance_of_child_and_parents() {
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Parent, &grandChild);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(OtherParent, &grandChild);
        DN_APP_UNITY_TEST_ASSERT_INSTANCE_OF(Child, &grandChild);
    }

    void test_parent_is_not_instance_of_other_parent() {
        DN_APP_UNITY_TEST_ASSERT_NOT_INSTANCE_OF(Parent, &otherParent);
        DN_APP_UNITY_TEST_ASSERT_NOT_INSTANCE_OF(OtherParent, &parent);
    }

    void test_parent_is_not_instance_of_child_and_grandchild() {
        DN_APP_UNITY_TEST_ASSERT_NOT_INSTANCE_OF(Child, &parent);
        DN_APP_UNITY_TEST_ASSERT_NOT_INSTANCE_OF(GrandChild, &parent);
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_instance_of_itself);
    RUN_TEST(test_child_is_instance_of_parents);
    RUN_TEST(test_grandchild_is_instance_of_child_and_parents);
    RUN_TEST(test_parent_is_not_instance_of_other_parent);
    RUN_TEST(test_parent_is_not_instance_of_child_and_grandchild);

    return UNITY_END();
}
