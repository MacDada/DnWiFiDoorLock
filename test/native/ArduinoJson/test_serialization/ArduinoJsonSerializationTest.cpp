#include <cstring>

#include "ArduinoJson.h"
#include "unity.h"

namespace {
    // language=JSON
    const auto expectedSerialized =
        R"({"root":{"foo":"foo_val","bar":"bar_val","baz":["baz_val_1","baz_val_2"]}})";

    const auto serializedSize = strlen(expectedSerialized) + 1;

    const auto documentSize =
        JSON_OBJECT_SIZE(1)
        + JSON_OBJECT_SIZE(3)
        + JSON_ARRAY_SIZE(2);

    auto testStaticJsonDocument() -> void {
        auto json = StaticJsonDocument<documentSize>{};

        json["root"]["foo"] = "foo_val";
        json["root"]["bar"] = "bar_val";

        json["root"]["baz"].add("baz_val_1");
        json["root"]["baz"].add("baz_val_2");

        TEST_ASSERT_FALSE(json.overflowed());

        char serialized[serializedSize];

        serializeJson(json, serialized, serializedSize);

        TEST_ASSERT_EQUAL_STRING(expectedSerialized, serialized);
    }

    auto testDynamicJsonDocument() -> void {
        auto json = DynamicJsonDocument{documentSize};

        json["root"]["foo"] = "foo_val";
        json["root"]["bar"] = "bar_val";

        json["root"]["baz"].add("baz_val_1");
        json["root"]["baz"].add("baz_val_2");

        TEST_ASSERT_FALSE(json.overflowed());

        char serialized[serializedSize];

        serializeJson(json, serialized, serializedSize);

        TEST_ASSERT_EQUAL_STRING(expectedSerialized, serialized);
    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(testStaticJsonDocument);
    RUN_TEST(testDynamicJsonDocument);

    return UNITY_END();
}
