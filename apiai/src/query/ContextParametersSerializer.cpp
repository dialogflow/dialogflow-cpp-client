/**
 * Copyright 2017 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ContextParametersSerializer.h"

#include <cJSON.h>
#include <vector>

#include <iostream>

#include <apiai/exceptions/JSONException.h>

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

const map<string, shared_ptr<Element>> ContextParametersSerializer::serialize(cJSON *source) {
    if (source->type == cJSON_Object) {
        auto element = serialize_element(source);

//        std::cout << element.isArray() << std::endl;
//        std::cout << element.isBool() << std::endl;
//        std::cout << element.isString() << std::endl;
//        std::cout << element.isObject() << std::endl;
//        std::cout << element.isNumber() << std::endl;

        return element->asObject();
    }

    throw JSONException("Wrong type. Expected Object.");
}

shared_ptr<Element> ContextParametersSerializer::serialize_element(cJSON *json_element) {
    if (json_element->type == cJSON_Object) {
        map<string, shared_ptr<Element>> object;

        auto keys = all_keys(json_element);
        for(string& key: keys) {
            object[key] = serialize_element(cJSON_GetObjectItem(json_element, key.c_str()));
        }

        return shared_ptr<Element>(new ObjectElement(object));
    } else if (json_element->type == cJSON_Array) {
        vector<shared_ptr<Element>> array;

        int size = cJSON_GetArraySize(json_element);
        for (int i = 0; i < size; i++) {
            cJSON *array_element = cJSON_GetArrayItem(json_element, i);

            array.push_back(serialize_element(array_element));
        }

        return shared_ptr<Element>(new ArrayElement(array));
    } else if (json_element->type == cJSON_String) {
        std::string string(json_element->valuestring);

        return shared_ptr<Element>(new StringElement(string));
    } else if (json_element->type == cJSON_False || json_element->type == cJSON_True) {
        if (json_element->type == cJSON_True) {
            return shared_ptr<Element>(new BoolElement(true));
        } else {
            return shared_ptr<Element>(new BoolElement(false));
        }
    } else if (json_element->type == cJSON_Number) {
        return shared_ptr<Element>(new NumberElement(json_element->valuedouble));
    } else if (json_element->type == cJSON_NULL) {
        throw JSONException("Unexpected type in json response");
    } else {
        throw JSONException("Unexpected type in json response");
    }
}

