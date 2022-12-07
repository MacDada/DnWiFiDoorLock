#include <unity.h>

#include "DnApp/Unity/asserts.h"
#include "DnApp/Unity/functions.h"

using DnApp::Unity::instance_of;

class Parent {} parent;

class OtherParent {} otherParent;

class Child: public Parent, OtherParent {} child;

class GrandChild: public Child {} grandChild;

void test_instance_of_itself() {
    TEST_ASSERT_TRUE(instance_of<Parent>(&parent));
    TEST_ASSERT_TRUE(instance_of<OtherParent>(&otherParent));
    TEST_ASSERT_TRUE(instance_of<Child>(&child));
    TEST_ASSERT_TRUE(instance_of<GrandChild>(&grandChild));

    TEST_ASSERT_INSTANCE_OF(Parent, &parent);
    TEST_ASSERT_INSTANCE_OF(OtherParent, &otherParent);
    TEST_ASSERT_INSTANCE_OF(Child, &child);
    TEST_ASSERT_INSTANCE_OF(GrandChild, &grandChild);
}

void test_child_is_instance_of_parents() {
    TEST_ASSERT_TRUE(instance_of<Parent>(&child));
    TEST_ASSERT_TRUE(instance_of<OtherParent>(&child));

    TEST_ASSERT_INSTANCE_OF(Parent, &child);
    TEST_ASSERT_INSTANCE_OF(OtherParent, &child);
}

void test_grandchild_is_instance_of_child_and_parents() {
    TEST_ASSERT_TRUE(instance_of<Parent>(&grandChild));
    TEST_ASSERT_TRUE(instance_of<OtherParent>(&grandChild));
    TEST_ASSERT_TRUE(instance_of<Child>(&grandChild));

    TEST_ASSERT_INSTANCE_OF(Parent, &grandChild);
    TEST_ASSERT_INSTANCE_OF(OtherParent, &grandChild);
    TEST_ASSERT_INSTANCE_OF(Child, &grandChild);
}

void test_parent_is_not_instance_of_other_parent() {
    TEST_ASSERT_FALSE(instance_of<Parent>(&otherParent));
    TEST_ASSERT_FALSE(instance_of<OtherParent>(&parent));

    TEST_ASSERT_NOT_INSTANCE_OF(Parent, &otherParent);
    TEST_ASSERT_NOT_INSTANCE_OF(OtherParent, &parent);
}

void test_parent_is_not_instance_of_child_and_grandchild() {
    TEST_ASSERT_FALSE(instance_of<Child>(&parent));
    TEST_ASSERT_FALSE(instance_of<GrandChild>(&parent));

    TEST_ASSERT_NOT_INSTANCE_OF(Child, &parent);
    TEST_ASSERT_NOT_INSTANCE_OF(GrandChild, &parent);
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
