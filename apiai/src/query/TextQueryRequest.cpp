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

#include <apiai/query/TextQueryRequest.h>

#include "cJSON.h"

#include <apiai/query/response/Response.h>
#include <apiai/query/request/QueryText.h>
#include "request/QueryTextSerialize.h"

#include "../http/RequestConnectionImpl.h"

using namespace std;
using namespace ai::query::request;
using namespace ai::query::response;

TextQueryRequest::TextQueryRequest(
        const std::shared_ptr<QueryText> &query,
        const std::string &language,
        const Credentials &credentials,
        const Parameters &parameters): QueryRequest(language, credentials, parameters), query(query)
{
    if (!query.get()) {
        throw InvalidArgumentException("Query cannot be null");
    }
}

Response TextQueryRequest::perform() {
    cJSON *root = cJSON_CreateObject();

    shared_ptr<QueryTextSerialize> serialize_object(new QueryTextSerialize());
    query->accept(*serialize_object);

    cJSON_AddItemToObject(root, "query", serialize_object->getQuery_element());
    cJSON_AddItemToObject(root, "lang", cJSON_CreateString(this->getLanguage().c_str()));
    cJSON_AddItemToObject(root, "sessionId", cJSON_CreateString(this->getParameters().getSessionId().c_str()));

    auto json_contexts = cJSON_CreateArray();
    for (auto& context: this->getParameters().getContexts()) {
        auto json_context = cJSON_CreateObject();
        cJSON_AddItemToObject(json_context, "name", cJSON_CreateString(context.getName().c_str()));

        auto json_parameters = cJSON_CreateObject();
        for (auto& parameter: context.getParameters()) {
            cJSON_AddItemToObject(json_parameters, parameter.first.c_str(), cJSON_CreateString(parameter.second.c_str()));
        }

        cJSON_AddItemToObject(json_context, "parameters", json_parameters);

        if (context.getLifespan() >= 0) {
            cJSON_AddNumberToObject(json_context, "lifepan", context.getLifespan());
        }

        cJSON_AddItemToArray(json_contexts, json_context);
    }

    cJSON_AddItemToObject(root, "contexts", json_contexts);

    auto json_entities = cJSON_CreateArray();
    for (auto& entity: this->getParameters().getEntities()) {
        auto json_entity = cJSON_CreateObject();
        cJSON_AddItemToObject(json_entity, "name", cJSON_CreateString(entity.getName().c_str()));

        auto entries_json_array = cJSON_CreateArray();

        for (auto& entry: entity.getEntries()) {
            auto json_entry = cJSON_CreateObject();
            cJSON_AddItemToObject(json_entry, "value", cJSON_CreateString(entry.getValue().c_str()));

            auto json_synonyms = cJSON_CreateArray();

            for (auto& synonym: entry.getSynonyms()) {
                cJSON_AddItemToArray(json_synonyms, cJSON_CreateString(synonym.c_str()));
            }

            cJSON_AddItemToObject(json_entry, "synonyms", json_synonyms);

            cJSON_AddItemToArray(entries_json_array, json_entry);
        }

        cJSON_AddItemToObject(json_entity, "entries", entries_json_array);

        cJSON_AddItemToArray(json_entities, json_entity);
    }

    cJSON_AddItemToObject(root, "entities", json_entities);

    auto json = cJSON_Print(root);

//    cout << json << endl;

    impl->setBody(json);
    free(json);

    cJSON_Delete(root);

    return Request::perform();
}

const std::shared_ptr<QueryText> &TextQueryRequest::getQuery() const
{
    return query;
}
