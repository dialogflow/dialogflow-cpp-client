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

#include <apiai/query/response/Result.h>
#include <apiai/query/response/Fulfillment.h>

#include "indent_stream.h"

#include <memory>
#include <string>
#include <ostream>

using namespace std;
using namespace ai::query::response;

Result::Result(const string source,
               const string resolvedQuery,
               const shared_ptr<string> action,
               const shared_ptr<Fulfillment> fulfillment,
               const Metadata metadata,
               map<string, shared_ptr<Element>> parameters,
               const vector<ai::query::response::Context> contexts):
    source(source), resolvedQuery(resolvedQuery), action(action), fulfillment(fulfillment), metadata(metadata), parameters(parameters), contexts(contexts)
{

}

Result::~Result() {

}

vector<Context> Result::getContexts() const
{
    return contexts;
}

Metadata Result::getMetadata() const
{
    return metadata;
}

map<string, shared_ptr<Element>>Result::getParameters() const
{
    return parameters;
}

shared_ptr<Fulfillment> Result::getFulfillment() const
{
    return fulfillment;
}

string Result::getSource() const
{
    return source;
}

string Result::getResolvedQuery() const
{
    return resolvedQuery;
}

shared_ptr<string> Result::getAction() const
{
    return action;
}

namespace ai {
    namespace query {
        namespace response {
            ostream& operator << (ostream& os, const Result& result) {

                os << "Result:" << endl;
                os << "    " << "source: " << result.source << endl;
                os << "    " << "resolvedQuey: " << result.resolvedQuery << endl;
                os << "    " << "action: ";

                if (result.action.get()) {
                    os << *result.action;
                } else {
                    os << "NULL";
                }

                os << endl;

                os << "fufillment: ";

                if (result.fulfillment.get()) {
                    ai::utils::indent_stream indent_stream(os);
                    indent_stream << *result.fulfillment.get();
                } else {
                    os << "NULL";
                }

                os << endl;

                os << "metadata: ";
                {
                    ai::utils::indent_stream indent_stream(os);
                    indent_stream << result.metadata;
                }

                ////

                os << "parameters: {\n";
                ai::utils::indent_stream indent_stream(os);
                for (auto key_value: result.parameters) {
                    auto key = key_value.first;
                    auto& element = *key_value.second;

                    indent_stream << "\"" << key << "\": ";
                    std::ostream& temp = indent_stream;

                    ai::utils::indent_stream indent_stream2(temp);

                    indent_stream2 << element << endl;
                }

                os << "    " << "}\n";

                ////

                os << "contexts: [" << endl;

//                ai::utils::indent_stream indent_stream(os);
                for (auto context: result.contexts) {
                    indent_stream << "{" << endl;

                    ostream& qwe = indent_stream;
                    ai::utils::indent_stream indent_stream2(qwe);

                    indent_stream2 << context;
                    indent_stream << "}, " << endl;
                }

                os << "]";

                return os;
            }
        }
    }
}
