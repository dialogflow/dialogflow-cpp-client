#include "TextQueryRequest.h"

using namespace std;
using namespace ai::query::request;

std::shared_ptr<QueryText> TextQueryRequest::getQuery() const
{
    return query;
}
