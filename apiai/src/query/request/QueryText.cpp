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

#include "QueryTextVisitor.h"
#include <apiai/query/request/QueryText.h>


using namespace std;
using namespace ai::query::request;

const std::shared_ptr<QueryText> QueryText::One(string query) {
    return std::shared_ptr<QueryText>(new QueryOne(query));
}

const std::shared_ptr<QueryText> QueryText::Multiple(std::vector<std::string> query){
    return std::shared_ptr<QueryText>(new QueryMultipleStrings(query));
}

const std::shared_ptr<QueryText> QueryText::Multiple(std::vector<QueryVariant> query){
    return std::shared_ptr<QueryText>(new QueryMultipleVariants(query));
}

void QueryOne::accept(QueryTextVisitor &serizalize) const
{
    serizalize.visit(*this);
}

void QueryMultipleStrings::accept(QueryTextVisitor &serizalize) const
{
    serizalize.visit(*this);
}

void QueryMultipleVariants::accept(QueryTextVisitor &serizalize) const
{
    serizalize.visit(*this);
}
