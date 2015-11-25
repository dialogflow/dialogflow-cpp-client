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

map<string, Element> ContextParametersSerializer::serialize(cJSON *source) {

}

Element ContextParametersSerializer::serialize_element(cJSON *json_element) {
    if (json_element->type == cJSON_Object) {
        map<string, Element> object;

        auto keys = all_keys(json_element);
        for(string& key: keys) {
            object[key] = serialize_element(cJSON_GetObjectItem(json_element, key.c_str()));
        }

        return
    }
}

