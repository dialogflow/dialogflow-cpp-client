#ifndef QUERYRESPONSE_H
#define QUERYRESPONSE_H

#include "Result.h"

namespace ai {
    namespace query {
        class QueryRequest;

        namespace response {
            class QueryResponse
            {
            public:
                const std::string identifier;
                const std::string timestamp;
                const Result result;

                virtual ~QueryResponse();

                friend std::ostream& operator << (std::ostream& os, const QueryResponse& query_response);

                friend class ai::query::QueryRequest;

            private:
                QueryResponse(const std::string identifier, const std::string timestamp, const Result result);
            };

            std::ostream& operator << (std::ostream& os, const QueryResponse& query_response);
        }
    }
}

#endif // QUERYRESPONSE_H
