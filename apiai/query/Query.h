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
            const Result result;
        private:
            QueryResponse(const std::string identifier, const std::time_t timestamp, const Result result);
        };

        class QueryRequest: public Request {
        private:
            QueryRequest(const QueryRequest&);
        public:
            const std::string language;
            virtual void perform() override;
            QueryRequest(Credentials credentials);
        };
    }
}

#endif // QUERY_H
