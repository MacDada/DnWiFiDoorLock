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

    Parent parent{};

    OtherParent otherParent{};

    Child child{};

    GrandChild grandChild{};

    void test_instance_of_itself() {
        TEST_ASSERT_TRUE(instanceOf<Parent>(&parent));
        TEST_ASSERT_TRUE(instanceOf<OtherParent>(&otherParent));
        TEST_ASSERT_TRUE(instanceOf<Child>(&child));
        TEST_ASSERT_TRUE(instanceOf<GrandChild>(&grandChild));
    }

    void test_child_is_instance_of_parents() {
        TEST_ASSERT_TRUE(instanceOf<Parent>(&child));
        TEST_ASSERT_TRUE(instanceOf<OtherParent>(&child));
    }

    void test_grandchild_is_instance_of_child_and_parents() {
        TEST_ASSERT_TRUE(instanceOf<Parent>(&grandChild));
        TEST_ASSERT_TRUE(instanceOf<OtherParent>(&grandChild));
        TEST_ASSERT_TRUE(instanceOf<Child>(&grandChild));
    }

    void test_parent_is_not_instance_of_other_parent() {
        TEST_ASSERT_FALSE(instanceOf<Parent>(&otherParent));
        TEST_ASSERT_FALSE(instanceOf<OtherParent>(&parent));
    }

    void test_parent_is_not_instance_of_child_and_grandchild() {
        TEST_ASSERT_FALSE(instanceOf<Child>(&parent));
        TEST_ASSERT_FALSE(instanceOf<GrandChild>(&parent));
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
