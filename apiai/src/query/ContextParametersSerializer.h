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

#ifndef CONTEXTPARAMETERSSERIALIZER_H
#define CONTEXTPARAMETERSSERIALIZER_H

#include <string>
#include <map>

#include <apiai/query/response/Context.h>

class cJSON;

namespace ai{
    namespace query {
        namespace response {
            class ContextParametersSerializer
            {
            public:
                // TODO: Is it OK that the outgoing map is marked as 'const'.
                static const std::map<std::string, std::shared_ptr<Element>> serialize(cJSON *source);
            private:
                // TODO: It would be nice to return a smart pointer to a new element rather than an element itself. Too many copies happen.
                static std::shared_ptr<Element> serialize_element(cJSON *json_element);
                ContextParametersSerializer();
            };
        }
    }
}

#endif // CONTEXTPARAMETERSSERIALIZER_H
