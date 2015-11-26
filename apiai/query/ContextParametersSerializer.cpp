#include "ContextParametersSerializer.h"

#include <vector>

using namespace std;
using namespace ai::query::response;

static vector<string> all_keys(cJSON *object) {
    vector<string> keys;
    cJSON *child = object->child;

    while (child) {
        auto key = string(child->string);
        keys.push_back(key);
        child = child->next;
    }

    return keys;
}

const map<string, Element> ContextParametersSerializer::serialize(cJSON *source) {
    if (source->type == cJSON_Object) {
        return serialize_element(source).asObject();
    }

    throw JSONException("Wrong type. Expected Object.");
}

Element ContextParametersSerializer::serialize_element(cJSON *json_element) {
    if (json_element->type == cJSON_Object) {
        map<string, Element> object;

        auto keys = all_keys(json_element);
        for(string& key: keys) {
            object[key] = serialize_element(cJSON_GetObjectItem(json_element, key.c_str()));
        }

        return ObjectElement(object);
    } else if (json_element->type == cJSON_Array) {
        vector<Element> array;

        int size = cJSON_GetArraySize(json_element);
        for (int i = 0; i < size; i++) {
            cJSON *array_element = cJSON_GetArrayItem(json_element, i);

            array.push_back(serialize_element(array_element));
        }

        return ArrayElement(array);
    } else if (json_element->type == cJSON_String) {
        std::string string(json_element->valuestring);

        return StringElement(string);
    } else if (json_element->type == cJSON_False || json_element->type == cJSON_True) {
        if (json_element->type == cJSON_True) {
            return BoolElement(true);
        } else {
            return BoolElement(false);
        }
    } else if (json_element->type == cJSON_Number) {
        return NumberElement(json_element->valuedouble);
    } else if (json_element->type == cJSON_NULL) {
        throw JSONException("Unexpected type in json response");
    } else {
        throw JSONException("Unexpected type in json response");
    }
}

