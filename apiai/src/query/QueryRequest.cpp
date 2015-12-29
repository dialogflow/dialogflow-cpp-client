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

using namespace std;
using namespace ai::query;
using namespace ai::query::request;
using namespace ai::query::response;

QueryRequest::QueryRequest(const std::string &language,
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

const std::string &QueryRequest::getLanguage() const
{
    return language;
}

Response QueryRequest::serialize(const std::string &response) {
//    cout << response << endl;
    throw ai::InvalidArgumentException("Language cannot be zero size");

    cJSON *root = cJSON_Parse(response.c_str());

    if (root) {
        try {
            std::string identifier = jsonString(root, "id");
            std::string timestamp = jsonString(root, "timestamp");

            auto result_json = jsonObject(root, "result");

            std::string source = jsonString(result_json, "source");
            std::string resolvedQuery = jsonString(result_json, "resolvedQuery");

            auto action_pointer = std::shared_ptr<std::string>(nullptr);

            try {
                std::string action = jsonString(result_json, "action");
                action_pointer = std::shared_ptr<std::string>(new std::string(action));
            } catch (...) {
                // if action not exist then ignore it
            }

            auto fulfillment_pointer = std::shared_ptr<Fulfillment>(nullptr);

            try {
                auto fulfillment_json = jsonObject(result_json, "fulfillment");
                std::string speech = jsonString(fulfillment_json, "speech");
                fulfillment_pointer = std::shared_ptr<Fulfillment>(new Fulfillment(speech));
            } catch (...) {
                // if fulfillment not exist then ignore it
            }

            std::shared_ptr<Metadata> metadata_pointer(new Metadata());

            try {
                auto metadata_json = jsonObject(result_json, "metadata");
                std::string intentId = jsonString(metadata_json, "intentId");
                std::string intentName = jsonString(metadata_json, "intentName");

                Metadata metadata = Metadata(
                            std::shared_ptr<std::string>(new std::string(intentId)),
                            std::shared_ptr<std::string>(new std::string(intentName))
                            );

                metadata_pointer = std::shared_ptr<Metadata>(new Metadata(metadata));
            } catch (...) {
                // if one field of metadata not exist then ignore this fields
            }

            std::vector <ai::query::response::Context> contexts;

            try {
                auto contexts_array_json = jsonArray(result_json, "contexts");

                for (int i = 0; i < cJSON_GetArraySize(contexts_array_json); i++) {
                    auto context_json = cJSON_GetArrayItem(contexts_array_json, i);

                    auto name = jsonString(context_json, "name");
                    auto lifespan = -1;

                    try {
                        lifespan = jsonInt(context_json, "lifespan");
                    } catch(...) {}

                    std::map<std::string, ai::query::response::Element> params;

                    try {
                        auto json_params = jsonObject(context_json, "parameters");

                        params = ai::query::response::ContextParametersSerializer::serialize(json_params);
                    } catch(...){}

                    contexts.push_back(ai::query::response::Context(name, lifespan, params));
                }
            } catch (...) {
                throw;
            }

            auto result = Result(source, resolvedQuery, action_pointer, fulfillment_pointer, *metadata_pointer.get(), contexts);

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
