#include "Query.h"

#include <iostream>

#include "cJSON.h"

namespace ai {
    namespace Query {
        Result::Result(const std::string source, const std::string resolvedQuery, const std::string action):
            source(source), resolvedQuery(resolvedQuery), action(action)
        {

        }

        QueryResponse::QueryResponse(std::string identifier, std::time_t timestamp):
            identifier(identifier), timestamp(timestamp)
        {

        }

        QueryRequest::QueryRequest(std::string query, std::string language, Credentials credentials): Request(credentials), language("en"), query(query) {
            httpRequest
                    .addHeader("Content-Type", "application/json")
                    .addHeader("Transfer-Encoding", "chunked");
        }

        QueryResponse QueryRequest::perform() {
            cJSON *root = cJSON_CreateObject();

            cJSON_AddItemToObject(root, "query", cJSON_CreateString(this->query.c_str()));
            cJSON_AddItemToObject(root, "lang", cJSON_CreateString(this->language.c_str()));

            auto json = cJSON_PrintUnformatted(root);

            httpRequest.setBody(json);
            free(json);

            cJSON_Delete(root);

            return Request::perform();
        }

        QueryResponse QueryRequest::fromResponse(std::string response) {
            std::cout << response << std::endl;

            cJSON *root = cJSON_Parse(response.c_str());

            std::string identifier;

            if (root) {
                try {
                    cJSON *id = cJSON_GetObjectItem(root, "id");

                    if (id) {
                        if (id->type == cJSON_String) {
                            identifier = id->valuestring;
                        } else {
                            // throw missing type if "id"
                        }
                    } else {
                        // throw missing key "status"
                    }
                } catch(...) {
                    cJSON_Delete(root);
                    throw;
                }
            } else {
                //throw: cannot parse response, response is not json
            }

            return QueryResponse(identifier, std::time(nullptr));
        }

        QueryRequest::~QueryRequest() {}
    }
}
