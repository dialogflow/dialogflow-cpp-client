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
 
#ifndef QUERYRESPONSE_H
#define QUERYRESPONSE_H

#include "Result.h"

namespace ai {
    namespace query {
        namespace request {
            class QueryRequest;
        }

        namespace response {
            class Response
            {
            public:
                const std::string identifier;
                const std::string timestamp;
                const Result result;

                virtual ~Response();

                friend std::ostream& operator << (std::ostream& os, const Response& query_response);

                friend class ai::query::request::QueryRequest;

            private:
                Response(const std::string identifier, const std::string timestamp, const Result result);
            };

            std::ostream& operator << (std::ostream& os, const Response& query_response);
        }
    }
}

#endif // QUERYRESPONSE_H
