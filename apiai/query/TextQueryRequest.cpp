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

    auto json = cJSON_Print(root);

    httpRequest.setBody(json);
    free(json);

    cJSON_Delete(root);

    return Request::perform();
}

std::shared_ptr<QueryText> TextQueryRequest::getQuery() const
{
    return query;
}
