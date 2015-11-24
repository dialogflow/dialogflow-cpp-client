#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <ctime>

#include "../http/Request.h"

namespace ai {
    namespace Query {
        class Result {
        public:
            const std::string source;
            const std::string resolvedQuery;
            const std::string action;
        private:
            Result(const std::string source, const std::string resolvedQuery, const std::string action);
        };

        class QueryResponse
        {
        public:
            const std::string identifier;
            const std::time_t timestamp;
        private:
            QueryResponse(const std::string identifier, const std::time_t timestamp);

            friend class QueryRequest;
        };

        class QueryRequest: public Request<QueryResponse> {
        public:
            const std::string language;
            const std::string query;

            virtual QueryResponse perform() override;

            QueryRequest(std::string query, std::string language, Credentials credentials);
            virtual ~QueryRequest();
        private:
            QueryRequest(const QueryRequest&);
        protected:
            virtual QueryResponse fromResponse(std::string response) override;
        };
    }
}

#endif // QUERY_H
