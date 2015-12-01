#include "Context.h"

#include "indent_stream.h"

using namespace std;
using namespace ai::query::response;

bool Element::isObject()    const   { return false; }
bool Element::isNumber()    const   { return false; }
bool Element::isArray()     const   { return false; }
bool Element::isBool()      const   { return false; }
bool Element::isString()    const   { return false; }

map<string, Element>    Element::asObject()     const   { throw JSONException("Cannot cast value to Object type."); }
double                  Element::asDouble()     const   { throw JSONException("Cannot cast value to Double type."); }
int                     Element::asInteger()    const   { throw JSONException("Cannot cast value to Integer type."); }
vector<Element>         Element::asArray()      const   { throw JSONException("Cannot cast value to Array type."); }
bool                    Element::asBool()       const   { throw JSONException("Cannot cast value to Bool type."); }
string                  Element::asString()     const   { throw JSONException("Cannot cast value to String type."); }

Context::Context(
        string                  name,
        int                     lifespan,
        map<string, Element>    parameters
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

map<string, Element> Context::getParameters() const
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

                os << "    " << "parameters: {";

                ai::utils::indent_stream indent_stream(os);
                for (auto key_value: context.parameters) {
                    auto key = key_value.first;
                    auto element = key_value.second;

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
