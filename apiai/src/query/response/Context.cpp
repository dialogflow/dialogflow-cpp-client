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
