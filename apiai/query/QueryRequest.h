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
                // TODO: It would be nice to decorate the getters as shown below.
//                const std::string &getLanguage() const;
//                const std::shared_ptr<QueryText> &getQuery() const;
                std::string getLanguage() const;
                std::shared_ptr<QueryText> getQuery() const;

                virtual response::Response perform() override;

                // TODO: It would be nice to decorate the constructor as shown below.
//                QueryRequest(const std::shared_ptr<QueryText>& query, const std::string &language, const Credentials &credentials);
                QueryRequest(std::shared_ptr<QueryText> query, std::string language, Credentials credentials);
                virtual ~QueryRequest();
            private:
                // TODO: It's also necessary to disallow assignment. It's better use DISALLOW_COPY_AND_ASSIGN by Google.
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
