#include "QueryTextSerialize.h"
#include <apiai/query/request/QueryText.h>

#include <iostream>

using namespace std;
using namespace ai::query::request;

QueryTextSerialize::QueryTextSerialize(){}

cJSON *QueryTextSerialize::getQuery_element() const
{
    return query_element;
}

void QueryTextSerialize::visit(const QueryOne& ref)
{
    auto cstring = ref.query.c_str();

    query_element = cJSON_CreateString(cstring);
}

void QueryTextSerialize::visit(const QueryMultipleStrings& ref)
{
    auto elements = ref.query;

    auto array = cJSON_CreateArray();

    for (auto& element: elements) {
        auto json_element = cJSON_CreateString(element.c_str());
        cJSON_AddItemToArray(array, json_element);
    }

    query_element = array;

    cout << "!!!!!!" << endl;
}

void QueryTextSerialize::visit(const QueryMultipleVariants& ref)
{
    auto elements = ref.query;

    auto array = cJSON_CreateArray();

    for (auto& element: elements) {
        auto text_json_element = cJSON_CreateString(element.getText().c_str());
        auto confidence_json_element = cJSON_CreateNumber(element.getConfidence());

        auto json_element = cJSON_CreateObject();
        cJSON_AddItemToObject(json_element, "text", text_json_element);
        cJSON_AddItemToObject(json_element, "confidence", confidence_json_element);

        cJSON_AddItemToArray(array, json_element);
    }

    query_element = array;

    cout << "!!!!!!" << endl;
}
