#ifndef RESULT_H
#define RESULT_H

#include "Metadata.h"
#include "Fulfillment.h"
#include "Context.h"

#include <vector>

namespace ai {
    namespace query {
        class QueryRequest;

        namespace response {
            class Result {
            public:
                std::string getSource() const;
                std::string getResolvedQuery() const;
                std::shared_ptr<std::string> getAction() const;
                std::shared_ptr<Fulfillment> getFulfillment() const;
                Metadata getMetadata() const;

                virtual ~Result();

                friend std::ostream& operator << (std::ostream& os, const Result& result);

            private:
                const std::string source;
                const std::string resolvedQuery;
                const std::shared_ptr<std::string> action;
                const std::shared_ptr<Fulfillment> fulfillment;
                const Metadata metadata;
                const std::vector<Context> contexts;

                Result(const std::string source,
                       const std::string resolvedQuery,
                       const std::shared_ptr<std::string> action,
                       const std::shared_ptr<Fulfillment> fulfillment,
                       const Metadata metadata,
                       const std::vector<ai::query::response::Context> contexts);

                friend class ai::query::QueryRequest;
            };

            std::ostream& operator << (std::ostream& os, const Result& result);
        }
    }
}

#endif // RESULT_H
