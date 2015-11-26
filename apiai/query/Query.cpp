#include "Query.h"

#include <iostream>
#include <iomanip>

#include "ContextParametersSerializer.h"

#include "cJSON.h"
#include "cJSONUtils.h"
#include "../JSON/JSONException.h"

using namespace std;
using namespace ai::query;
using namespace ai::query::response;

QueryRequest::QueryRequest(std::string query, std::string language, Credentials credentials): Request(credentials), language("en"), query(query) {
    httpRequest
            .addHeader("Content-Type", "application/json")
            .addHeader("Transfer-Encoding", "chunked");
}

QueryResponse QueryRequest::perform() {
    cJSON *root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "query", cJSON_CreateString(this->query.c_str()));
    cJSON_AddItemToObject(root, "lang", cJSON_CreateString(this->language.c_str()));

    auto json = cJSON_Print(root);

    httpRequest.setBody(json);
    free(json);

    cJSON_Delete(root);

    return Request::perform();
}

QueryResponse QueryRequest::fromResponse(std::string response) {
    std::cout << response << std::endl;

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

//                    std::map<std::string, Element> qwe;

//                    auto q = new ObjectElement(qwe);
//                    auto a = new ArrayElement(std::vector<Element>());

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

            return QueryResponse(identifier, timestamp, result);
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
