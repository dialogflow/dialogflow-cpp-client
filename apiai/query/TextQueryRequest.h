#ifndef TEXTQUERYREQUEST_H
#define TEXTQUERYREQUEST_H

#include "QueryRequest.h"

#include <memory>
#include <string>
#include "request/QueryText.h"

namespace ai {
    namespace query {
        namespace request {
            class TextQueryRequest : public QueryRequest {
            public:
                TextQueryRequest(std::shared_ptr<QueryText> query,
                                 std::string language,
                                 Credentials credentials,
                                 Parameters parameters);
                std::shared_ptr<QueryText> getQuery() const;
            private:
                TextQueryRequest(const QueryRequest&);

                std::shared_ptr<QueryText> query;
            };
        }
    }
}

#endif // TEXTQUERYREQUEST_H
