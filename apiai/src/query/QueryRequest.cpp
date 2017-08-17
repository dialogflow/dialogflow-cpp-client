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

#include <apiai/query/QueryRequest.h>

#include <ctime>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>

#include "ContextParametersSerializer.h"
#include <apiai/query/request/QueryText.h>
#include "request/QueryTextSerialize.h"

#include "cJSON.h"
#include "cJSONUtils.h"
#include <apiai/exceptions/JSONException.h>

#include "../http/RequestConnectionImpl.h"

#include <apiai/exceptions/InvalidArgumentException.h>
#include <apiai/exceptions/ResponseErrorException.h>
#include <apiai/query/response/Fulfillment.h>

using namespace std;
using namespace ai::query;
using namespace ai::query::request;
using namespace ai::query::response;

QueryRequest::QueryRequest(const string &language,
                           const Credentials &credentials,
                           const Parameters &parameters):
    Request(credentials), language(language), parameters(parameters)
{
    if (language.size() == 0) {
        throw InvalidArgumentException("Language cannot be zero size");
    }

    impl->addHeader("Content-Type", "application/json; charset=utf-8")
            .addHeader("Transfer-Encoding", "chunked");
}

const string &QueryRequest::getLanguage() const
{
    return language;
}

response::Response QueryRequest::serialize(const string &response) {
    cJSON *root = cJSON_Parse(response.c_str());

    if (root) {
        try {
            auto status = jsonObject(root, "status");

            auto statusCode = jsonInt(status, "code");
            auto errorType = jsonString(status, "errorType");

            if (statusCode != 200 || errorType != "success") {
                auto errorDetails = jsonString(status, "errorDetails");
                throw ResponseErrorException(errorType, errorDetails, statusCode);
            }

            string identifier = jsonString(root, "id");
            string timestamp = jsonString(root, "timestamp");

            auto result_json = jsonObject(root, "result");

            string source = jsonString(result_json, "source");
            string resolvedQuery = jsonString(result_json, "resolvedQuery");

            auto action_pointer = shared_ptr<string>(nullptr);

            try {
                string action = jsonString(result_json, "action");
                action_pointer = shared_ptr<string>(new string(action));
            } catch (...) {
                // if action not exist then ignore it
            }

            auto fulfillment_pointer = shared_ptr<Fulfillment>(nullptr);

            try {
                auto fulfillment_json = jsonObject(result_json, "fulfillment");
                string speech = jsonString(fulfillment_json, "speech");
                fulfillment_pointer = shared_ptr<Fulfillment>(new Fulfillment(speech));
            } catch (...) {
                // if fulfillment not exist then ignore it
            }

            shared_ptr<Metadata> metadata_pointer(new Metadata());

            try {
                auto metadata_json = jsonObject(result_json, "metadata");
                string intentId = jsonString(metadata_json, "intentId");
                string intentName = jsonString(metadata_json, "intentName");

                Metadata metadata = Metadata(
                            shared_ptr<string>(new string(intentId)),
                            shared_ptr<string>(new string(intentName))
                            );

                metadata_pointer = shared_ptr<Metadata>(new Metadata(metadata));
            } catch (...) {
                // if one field of metadata not exist then ignore this fields
            }

            vector <Context> contexts;

            try {
                auto contexts_array_json = jsonArray(result_json, "contexts");

                for (int i = 0; i < cJSON_GetArraySize(contexts_array_json); i++) {
                    auto context_json = cJSON_GetArrayItem(contexts_array_json, i);

                    auto name = jsonString(context_json, "name");
                    auto lifespan = -1;

                    try {
                        lifespan = jsonInt(context_json, "lifespan");
                    } catch(...) {}

                    map<string, shared_ptr<Element>> params;

                    try {
                        auto json_params = jsonObject(context_json, "parameters");

                        params = ContextParametersSerializer::serialize(json_params);
                    } catch(...){}

                    contexts.push_back(Context(name, lifespan, params));
                }
            } catch (...) {
                throw;
            }

            map<string, shared_ptr<Element>> result_parameters;

            try {
                auto result_parameters_json = jsonObject(result_json, "parameters");

                if (result_parameters_json) {
                    result_parameters = ContextParametersSerializer::serialize(result_parameters_json);
                }
            } catch(...) {}

            auto result = Result(source, resolvedQuery, action_pointer, fulfillment_pointer, *metadata_pointer.get(), result_parameters, contexts);

            return Response(identifier, timestamp, result);
        } catch(...) {
            cJSON_Delete(root);
            throw;
        }
    } else {
        throw ai::JSONException("Cannot parse server response.");
    }
}

QueryRequest::~QueryRequest() {

}

const Parameters &QueryRequest::getParameters() const
{
    return parameters;
}
