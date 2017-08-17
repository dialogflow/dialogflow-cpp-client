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
