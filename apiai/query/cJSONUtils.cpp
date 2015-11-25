#include "cJSONUtils.h"

#include "../JSON/JSONException.h"

cJSON *jsonObject(cJSON *object, const char *key) {
    auto other = cJSON_GetObjectItem(object, key);
    if (!other) {
        throw ai::JSONException::MissingKey(key);
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

int jsonDouble(cJSON *object, const char *key) {
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
