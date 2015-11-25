#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <ctime>

#include "../http/Request.h"

namespace ai {
    namespace Query {
        class Metadata {
        public:
            std::shared_ptr<std::string> getIntentId() const;
            std::shared_ptr<std::string> getIntentName() const;

            virtual ~Metadata();
        private:

            Metadata();
            Metadata(std::shared_ptr<std::string> intentId, std::shared_ptr<std::string> intentName);

            const std::shared_ptr<std::string> intentId;
            const std::shared_ptr<std::string> intentName;

            friend class QueryRequest;
        };

        class Fulfillment {
        public:
            std::string getSpeech() const;

            virtual ~Fulfillment();
        private:
            Fulfillment(std::string speech);

            const std::string speech;

            friend class QueryRequest;
        };

        class Result {
        public:
            std::string getSource() const;
            std::string getResolvedQuery() const;
            std::shared_ptr<std::string> getAction() const;
            std::shared_ptr<Fulfillment> getFulfillment() const;
            Metadata getMetadata() const;

            virtual ~Result();

        private:
            const std::string source;
            const std::string resolvedQuery;
            const std::shared_ptr<std::string> action;
            const std::shared_ptr<Fulfillment> fulfillment;
            const Metadata metadata;

            Result(const std::string source,
                   const std::string resolvedQuery,
                   const std::shared_ptr<std::string> action,
                   const std::shared_ptr<Fulfillment> fulfillment,
                   const Metadata metadata);
            friend class QueryRequest;
        };

        class QueryResponse
        {
        public:
            const std::string identifier;
            const std::string timestamp;
            const Result result;

            virtual ~QueryResponse();
        private:
            QueryResponse(const std::string identifier, const std::string timestamp, const Result result);

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
