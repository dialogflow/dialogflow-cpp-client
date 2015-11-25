#include "Query.h"

#include <iostream>

#include "cJSON.h"
#include "cJSONUtils.h"
#include "../JSON/JSONException.h"

namespace ai {
    namespace Query {
        Metadata::Metadata(std::shared_ptr<std::string> intentId,
                           std::shared_ptr<std::string> intentName):
            intentId(intentId), intentName(intentName)
        {

        }

        Metadata::Metadata(): intentId(nullptr), intentName(nullptr) {

        }

        Metadata::~Metadata()
        {

        }

        Fulfillment::Fulfillment(std::string speech): speech(speech)
        {

        }

        Fulfillment::~Fulfillment() {}

        Result::Result(const std::string source,
                       const std::string resolvedQuery,
                       const std::shared_ptr<std::string> action,
                       const std::shared_ptr<Fulfillment> fulfillment,
                       const Metadata metadata):
            source(source), resolvedQuery(resolvedQuery), action(action), fulfillment(fulfillment), metadata(metadata)
        {

        }

        Result::~Result() {

        }

        Metadata Result::getMetadata() const
        {
            return metadata;
        }

        std::shared_ptr<Fulfillment> Result::getFulfillment() const
        {
            return fulfillment;
        }

        std::string Result::getSource() const
        {
            return source;
        }

        std::string Result::getResolvedQuery() const
        {
            return resolvedQuery;
        }

        std::shared_ptr<std::string> Result::getAction() const
        {
            return action;
        }

        QueryResponse::QueryResponse(const std::string identifier, const std::string timestamp, const Result result):
            identifier(identifier), timestamp(timestamp), result(result)
        {

        }

        QueryResponse::~QueryResponse() {}

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

                    auto result = Result(source, resolvedQuery, action_pointer, fulfillment_pointer, *metadata_pointer.get());

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

        std::string Fulfillment::getSpeech() const
        {
            return speech;
        }

        std::shared_ptr<std::string> Metadata::getIntentId() const
        {
            return intentId;
        }

        std::shared_ptr<std::string> Metadata::getIntentName() const
        {
            return intentName;
        }

    }
}
