#ifndef CJSONUTILS_H
#define CJSONUTILS_H

#include <string>

class cJSON;

cJSON *jsonObject(cJSON *object, const char *key);
cJSON *jsonArray(cJSON *object, const char *key);

int jsonInt(cJSON *object, const char *key);
double jsonDouble(cJSON *object, const char *key);
bool jsonBool(cJSON *object, const char *key);

std::string jsonString(cJSON *object, const char *key);

#endif // CJSONUTILS_H
