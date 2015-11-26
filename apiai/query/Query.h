#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <ctime>
#include <vector>
#include <map>

#include "response/QueryResponse.h"

#include "../http/Request.h"
#include "../JSON/JSONException.h"

namespace ai {
    namespace query {
        class QueryRequest: public Request<response::QueryResponse> {
        public:
            const std::string language;
            const std::string query;

            virtual response::QueryResponse perform() override;

            QueryRequest(std::string query, std::string language, Credentials credentials);
            virtual ~QueryRequest();
        private:
            QueryRequest(const QueryRequest&);
        protected:
            virtual response::QueryResponse fromResponse(std::string response) override;
        };
    }
}

#endif // QUERY_H
