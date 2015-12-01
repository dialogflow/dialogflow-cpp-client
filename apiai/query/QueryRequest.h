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
                std::string getLanguage() const;
                Parameters getParameters() const;

//                virtual response::Response perform() override;

                QueryRequest(std::string language, Credentials credentials, Parameters parameters);
                virtual ~QueryRequest();

            private:
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
