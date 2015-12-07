#include <apiai/query/response/Response.h>

#include <iostream>

#include "indent_stream.h"

using namespace std;

using namespace ai;
    using namespace query;
        using namespace response;
    using namespace utils;

Response::Response(const std::string identifier, const std::string timestamp, const Result result):
    identifier(identifier), timestamp(timestamp), result(result)
{

}

Response::~Response() {}

namespace ai {
    namespace query {
        namespace response {
            std::ostream& operator << (std::ostream& os, const Response& query_response) {
                os << "QueryResponse: " << std::endl;
                os << "    " << "identifier: " << query_response.identifier << std::endl;
                os << "    " << "timestamp: " << query_response.timestamp << std::endl;
                os << "    " << "result: ";

                indent_stream qwe(os);

                qwe << query_response.result;

                return os;
            }
        }
    }
}
