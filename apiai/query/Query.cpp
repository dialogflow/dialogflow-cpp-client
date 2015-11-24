#include "Query.h"

namespace ai {
    namespace Query {
        Result::Result(const std::string source, const std::string resolvedQuery, const std::string action):
            source(source), resolvedQuery(resolvedQuery), action(action)
        {

        }

        QueryResponse::QueryResponse(std::string identifier, std::time_t timestamp,  const Result result):
            identifier(identifier), timestamp(timestamp), result(result)
        {

        }

        void QueryRequest::perform() {

        }

        QueryRequest::QueryRequest(Credentials credentials): Request(credentials), language("en") {

        }
    }
}
