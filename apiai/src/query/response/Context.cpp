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

#include <apiai/query/response/Context.h>
#include <apiai/exceptions/JSONException.h>

#include "indent_stream.h"

using namespace std;
using namespace ai::query::response;

Context::Context(
        string                  name,
        int                     lifespan,
        map<string, std::shared_ptr<Element>>    parameters
        ): name(name), lifespan(lifespan), parameters(parameters)
{

}

int Context::getLifespan() const
{
    return lifespan;
}

string Context::getName() const
{
    return name;
}

map<string, shared_ptr<Element>> Context::getParameters() const
{
    return parameters;
}

namespace ai {
    namespace query {
        namespace response {
            std::ostream& operator << (std::ostream& os, const Context& context) {
                os << "Context:" << endl;
                os << "    " << "name: " << context.name << endl;
                os << "    " << "lifespan: " << context.lifespan << endl;

                os << "    " << "parameters: {\n";

                ai::utils::indent_stream indent_stream(os);
                for (auto key_value: context.parameters) {
                    auto key = key_value.first;
                    auto& element = *key_value.second;

                    indent_stream << "\"" << key << "\": ";
                    std::ostream& temp = indent_stream;

                    ai::utils::indent_stream indent_stream2(temp);

                    indent_stream2 << element << endl;
                }

                os << "    " << "}";

                return os;
            }

            std::ostream& operator << (std::ostream& os, const Element& element) {
                if (element.isBool()) {
                    os << element.asBool();
                } else if (element.isNumber()) {
                    os << element.asDouble();
                } else if (element.isString()) {
                    os << element.asString();
                } else if (element.isObject()) {
                    for (auto key_value: element.asObject()) {
                        os << "\"" << key_value.first << "\": ";
                        ai::utils::indent_stream indent_stream(os);
                        indent_stream << key_value.second;
                    }
                } else if (element.isArray()) {
                    auto subElements = element.asArray();

                    os << "[ ";

                    for (auto subElement: subElements) {
                        ai::utils::indent_stream indent_stream(os);
                        indent_stream << subElement;
                    }

                    os << "]";
                }
                return os;
            }
        }
    }
}
