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

#include <apiai/query/response/Response.h>

#include <iostream>

#include "indent_stream.h"

using namespace std;

using namespace ai;
    using namespace query;
        using namespace response;
    using namespace utils;

Response::Response(const std::string identifier, const std::string timestamp, const Result result):
    identifier(identifier), timestamp(timestamp), result(result)
{

}

Response::~Response() {}

namespace ai {
    namespace query {
        namespace response {
            std::ostream& operator << (std::ostream& os, const Response& query_response) {
                os << "QueryResponse: " << std::endl;
                os << "    " << "identifier: " << query_response.identifier << std::endl;
                os << "    " << "timestamp: " << query_response.timestamp << std::endl;
                os << "    " << "result: ";

                indent_stream qwe(os);

                qwe << query_response.result;

                return os;
            }
        }
    }
}
