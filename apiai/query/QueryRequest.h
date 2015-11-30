#ifndef QUERY_REQUEST_H
#define QUERY_REQUEST_H

#include <string>
#include <ctime>
#include <vector>
#include <map>

#include "response/Response.h"
#include "request/QueryText.h"

#include "../http/Request.h"
#include "../JSON/JSONException.h"

namespace ai {
    namespace query {
        namespace request {
            class QueryRequest: public Request<ai::query::response::Response> {
            public:
                std::string getLanguage() const;
                std::shared_ptr<QueryText> getQuery() const;

                virtual response::Response perform() override;

                QueryRequest(std::shared_ptr<QueryText> query, std::string language, Credentials credentials);
                virtual ~QueryRequest();
            private:
                QueryRequest(const QueryRequest&);

                std::string language;
                std::shared_ptr<QueryText> query;
            protected:
                virtual response::Response fromResponse(std::string response) override;
            };
        }
    }
}

#endif // QUERY_REQUEST_H
