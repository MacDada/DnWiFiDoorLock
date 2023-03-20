#include "ArduinoJson.h"
#include "unity.h"

namespace {
    // language=JSON
    auto expectedSerialized = R"({"root":{"foo":"foo_val","bar":"bar_val","baz":["baz_val_1","baz_val_2"]}})";

    auto& createJsonObject(DynamicJsonBuffer& jsonBuffer) {
        auto& object = jsonBuffer.createObject();

        TEST_ASSERT_TRUE(object.success());

        return object;
    }

    auto addToJsonArray(
        JsonArray& array,
        const JsonVariant& value
    ) -> void {
        TEST_ASSERT_TRUE(array.add(value));
    }

    auto setJsonValue(
        JsonObject& jsonObject,
        const char* const key,
        const JsonVariant& value
    ) -> void {
        TEST_ASSERT_TRUE(jsonObject.set(key, value));
    }

    auto testWithErrorHandling() -> void {
        auto jsonBuffer = DynamicJsonBuffer{};

        auto& baz = jsonBuffer.createArray();
        addToJsonArray(baz, "baz_val_1");
        addToJsonArray(baz, "baz_val_2");

        auto& root = createJsonObject(jsonBuffer);
        setJsonValue(root, "foo", "foo_val");
        setJsonValue(root, "bar", "bar_val");
        setJsonValue(root, "baz", baz);

        auto& json = createJsonObject(jsonBuffer);
        setJsonValue(json, "root", root);

        char jsonString[200];
        json.printTo(jsonString, 200);

        TEST_ASSERT_EQUAL_STRING(expectedSerialized, jsonString);
    }

    auto testWithoutErrorHandling() -> void {
        auto jsonBuffer = DynamicJsonBuffer{};

        auto& json = jsonBuffer.createObject();

        json["root"] = jsonBuffer.createObject();
        json["root"]["foo"] = "foo_val";
        json["root"]["bar"] = "bar_val";

        auto& baz = jsonBuffer.createArray();
        baz.add("baz_val_1");
        baz.add("baz_val_2");
        json["root"]["baz"] = baz;

        char jsonString[200];
        json.printTo(jsonString, 200);

        TEST_ASSERT_EQUAL_STRING(expectedSerialized, jsonString);
    }

//    auto testPoC1() -> void {
//        auto jsonFactory = JsonFactory{};
//
//        jsonFactory.onError([] () {
//
//        });
//
//        auto json = jsonFactory
//            .makeObject()
//            .with(
//                "root",
//                jsonFactory
//                    .makeObject()
//                    .set("foo", "foo_val")
//                    .set("bar", "bar_val")
//                    .set(
//                        "baz",
//                        jsonFactory
//                            .makeArray()
//                            .add("baz_val_1")
//                            .add("baz_val_2")
//                    )
//            );
//
//        if (json.success()) {
//            jsonResponse(request, json);
//        } else {
//            internalServerErrorResponse(
//                request,
//                PSTR("Failed to create jsonRoot")
//            );
//        }
//    }
//
//    auto testPoC2() -> void {
//        auto jsonFactory = JsonFactory{};
//
//        jsonFactory.onError([] () {
//
//        });
//
//        auto json = jsonFactory.makeObject();
//        json2["root"] = jsonFactory.makeObject();
//        json2["root"]["foo"] = "foo_val";
//        json2["root"]["bar"] = "bar_val";
//        json2["root"]["baz"] = jsonFactory.makeArray();
//        json2["root"]["baz"][] = "baz_val_1";
//        json2["root"]["baz"][] = "baz_val_2";
//
//        if (json.success()) {
//            jsonResponse(request, json);
//        } else {
//            internalServerErrorResponse(
//                request,
//                PSTR("Failed to create jsonRoot")
//            );
//        }
//    }
}

auto main() -> int {
    UNITY_BEGIN();

    RUN_TEST(testWithErrorHandling);
    RUN_TEST(testWithoutErrorHandling);

    return UNITY_END();
}
