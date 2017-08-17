/**
 * Copyright 2017 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
