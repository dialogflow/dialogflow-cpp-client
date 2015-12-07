#ifndef QUERYRESPONSE_H
#define QUERYRESPONSE_H

#include "Result.h"

namespace ai {
    namespace query {
        namespace request {
            class QueryRequest;
        }

        namespace response {
            class Response
            {
            public:
                const std::string identifier;
                const std::string timestamp;
                const Result result;

                virtual ~Response();

                friend std::ostream& operator << (std::ostream& os, const Response& query_response);

                friend class ai::query::request::QueryRequest;

            private:
                Response(const std::string identifier, const std::string timestamp, const Result result);
            };

            std::ostream& operator << (std::ostream& os, const Response& query_response);
        }
    }
}

#endif // QUERYRESPONSE_H
