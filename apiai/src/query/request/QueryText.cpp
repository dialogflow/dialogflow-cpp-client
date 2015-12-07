#include "QueryTextVisitor.h"
#include <apiai/query/request/QueryText.h>


using namespace std;
using namespace ai::query::request;

const std::shared_ptr<QueryText> QueryText::One(string query) {
    return std::shared_ptr<QueryText>(new QueryOne(query));
}

const std::shared_ptr<QueryText> QueryText::Multiple(std::vector<std::string> query){
    return std::shared_ptr<QueryText>(new QueryMultipleStrings(query));
}

const std::shared_ptr<QueryText> QueryText::Multiple(std::vector<QueryVariant> query){
    return std::shared_ptr<QueryText>(new QueryMultipleVariants(query));
}

void QueryOne::accept(QueryTextVisitor &serizalize) const
{
    serizalize.visit(*this);
}

void QueryMultipleStrings::accept(QueryTextVisitor &serizalize) const
{
    serizalize.visit(*this);
}

void QueryMultipleVariants::accept(QueryTextVisitor &serizalize) const
{
    serizalize.visit(*this);
}
