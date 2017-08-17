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

#include "cJSONUtils.h"
#include <cJSON.h>

#include <apiai/exceptions/JSONException.h>

cJSON *jsonObject(cJSON *object, const char *key) {
    auto other = cJSON_GetObjectItem(object, key);
    if (!other) {
        throw ai::JSONException::MissingKey(key);
    }

    return other;
}

cJSON *jsonArray(cJSON *object, const char *key) {
    auto other = cJSON_GetObjectItem(object, key);
    if (other->type != cJSON_Array) {
        throw ai::JSONException::TypeMismatch(key, "Array");
    }

    return other;
}

int jsonInt(cJSON *object, const char *key) {
    auto other = jsonObject(object, key);

    if (other->type != cJSON_Number) {
        throw ai::JSONException::TypeMismatch(key, "Int");
    }

    return other->valueint;
}

double jsonDouble(cJSON *object, const char *key) {
    auto other = jsonObject(object, key);

    if (other->type != cJSON_Number) {
        throw ai::JSONException::TypeMismatch(key, "Int");
    }

    return other->valuedouble;
}

bool jsonBool(cJSON *object, const char *key) {
    auto other = jsonObject(object, key);

    if (other->type != cJSON_False || other->type != cJSON_True) {
        throw ai::JSONException::TypeMismatch(key, "Bool");
    }

    if (other->type == cJSON_False) {
        return false;
    } else {
        return true;
    }
}

std::string jsonString(cJSON *object, const char *key) {
    auto other = jsonObject(object, key);

    if (other->type != cJSON_String) {
        throw ai::JSONException::TypeMismatch(key, "String");
    }

    return std::string(other->valuestring);
}
