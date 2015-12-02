#ifndef TEXTQUERYREQUEST_H
#define TEXTQUERYREQUEST_H

#include "QueryRequest.h"

#include <memory>
#include <string>

namespace ai {
    class Credentials;

    namespace query {
        namespace request {
            class Parameters;
            class QueryText;

            class TextQueryRequest : public QueryRequest {
            public:
                TextQueryRequest(const std::shared_ptr<QueryText> &query,
                                 const std::string &language,
                                 const Credentials &credentials,
                                 const Parameters &parameters);

                virtual response::Response perform() override;

                const std::shared_ptr<QueryText> &getQuery() const;
            private:
                TextQueryRequest(const QueryRequest&);

                std::shared_ptr<QueryText> query;
            };
        }
    }
}

#endif // TEXTQUERYREQUEST_H
