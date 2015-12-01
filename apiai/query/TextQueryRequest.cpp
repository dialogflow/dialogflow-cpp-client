#include "TextQueryRequest.h"

#include "cJSON.h"

#include "response/Response.h"
#include "request/QueryTextSerialize.h"

using namespace std;
using namespace ai::query::request;
using namespace ai::query::response;

TextQueryRequest::TextQueryRequest(
        std::shared_ptr<QueryText> query,
        std::string language,
        Credentials credentials,
        Parameters parameters): QueryRequest(language, credentials, parameters), query(query)
{
    if (!query.get()) {
        throw invalid_argument("Query cannot be null");
    }
}

Response TextQueryRequest::perform() {
    cJSON *root = cJSON_CreateObject();

    shared_ptr<QueryTextSerialize> serialize_object(new QueryTextSerialize());
    query->accept(*serialize_object);

    cJSON_AddItemToObject(root, "query", serialize_object->getQuery_element());
    cJSON_AddItemToObject(root, "lang", cJSON_CreateString(this->getLanguage().c_str()));

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

    httpRequest.setBody(json);
    free(json);

    cJSON_Delete(root);

    return Request::perform();
}

std::shared_ptr<QueryText> TextQueryRequest::getQuery() const
{
    return query;
}
