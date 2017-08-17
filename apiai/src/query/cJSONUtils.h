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
