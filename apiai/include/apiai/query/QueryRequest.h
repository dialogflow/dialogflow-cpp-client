#ifndef QUERY_REQUEST_H
#define QUERY_REQUEST_H

#include <string>

#include "response/Response.h"
#include "../http/Request.h"
#include "request/Parameters.h"

namespace ai {
    namespace query {
        namespace request {
            class QueryText;

            class QueryRequest: public Request<ai::query::response::Response> {
            public:
                const std::string &getLanguage() const;
                const Parameters &getParameters() const;

                QueryRequest(const std::string &language, const Credentials &credentials, const Parameters &parameters);
                virtual ~QueryRequest();

            private:
                // TODO: It's also necessary to disallow assignment. It's better use DISALLOW_COPY_AND_ASSIGN by Google.
                QueryRequest(const QueryRequest&);

                Parameters parameters;
                std::string language;
                std::shared_ptr<QueryText> query;
            public:
                virtual response::Response serialize(const std::string &response) override;
            };
        }
    }
}

#endif // QUERY_REQUEST_H
