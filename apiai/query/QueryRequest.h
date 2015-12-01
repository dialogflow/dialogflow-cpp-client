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

#include "request/Parameters.h"

namespace ai {
    namespace query {
        namespace request {

            class QueryRequest: public Request<ai::query::response::Response> {
            public:
                // TODO: It would be nice to decorate the getters as shown below.
//                const std::string &getLanguage() const;
                std::string getLanguage() const;
                Parameters getParameters() const;

                QueryRequest(std::string language, Credentials credentials, Parameters parameters);
                virtual ~QueryRequest();

            private:
                // TODO: It's also necessary to disallow assignment. It's better use DISALLOW_COPY_AND_ASSIGN by Google.
                QueryRequest(const QueryRequest&);

                Parameters parameters;
                std::string language;
                std::shared_ptr<QueryText> query;
            protected:
                virtual response::Response fromResponse(std::string response) override;
            };
        }
    }
}

#endif // QUERY_REQUEST_H
