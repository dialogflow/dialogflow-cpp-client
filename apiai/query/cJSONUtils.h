#ifndef CJSONUTILS_H
#define CJSONUTILS_H

#include <string>
#include <cJSON.h>

cJSON *jsonObject(cJSON *object, const char *key);

int jsonInt(cJSON *object, const char *key);
int jsonDouble(cJSON *object, const char *key);
bool jsonBool(cJSON *object, const char *key);

std::string jsonString(cJSON *object, const char *key);

#endif // CJSONUTILS_H
