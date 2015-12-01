#ifndef CJSONUTILS_H
#define CJSONUTILS_H

#include <string>
#include <cJSON.h> // TODO: Shouldn't we use forward declaration instead?

cJSON *jsonObject(cJSON *object, const char *key);
cJSON *jsonArray(cJSON *object, const char *key);

int jsonInt(cJSON *object, const char *key);
// FIXME: It seems a typo takes place.
//double jsonDouble(cJSON *object, const char *key);
int jsonDouble(cJSON *object, const char *key);
bool jsonBool(cJSON *object, const char *key);

std::string jsonString(cJSON *object, const char *key);

#endif // CJSONUTILS_H
