#include "Context.h"

using namespace std;
using namespace ai::query::response;

bool Element::isObject()    { return false; }
bool Element::isNumber()    { return false; }
bool Element::isInteger()   { return false; }
bool Element::isArray()     { return false; }
bool Element::isBool()      { return false; }
bool Element::isString()    { return false; }

map<string, Element>    Element::asObject()     const   { throw JSONException("Cannot cast value to Object type."); }
double                  Element::asDouble()     const   { throw JSONException("Cannot cast value to Double type."); }
int                     Element::asInteger()    const   { throw JSONException("Cannot cast value to Integer type."); }
vector<Element>         Element::asArray()      const   { throw JSONException("Cannot cast value to Array type."); }
bool                    Element::asBool()       const   { throw JSONException("Cannot cast value to Bool type."); }
string                  Element::asString()     const   { throw JSONException("Cannot cast value to String type."); }

//template <typename T>
//class ValueContainer {
//public:
//    ValueContainer(T value):value(value) {}

//    T getValue() const
//    {
//        return value;
//    }
//private:
//    T value;
//};

//class ObjectElement: public ValueContainer<map<string, Element>>, public Element{
//public:
//    ObjectElement(map<string, Element> value): ValueContainer(value) {}

//    virtual bool isObject() override { return true; }
//    virtual map<string, Element> asObject() const override { return this->getValue(); }
//};

//class ArrayElement: public ValueContainer<vector<Element>>, public Element {
//public:
//    ArrayElement(vector<Element> value): ValueContainer(value) {}

//    virtual bool isArray() override { return true; }
//    virtual vector<Element> asArray() const override { return this->getValue(); }
//};

//class StringElement: public ValueContainer<string>, public Element {
//public:
//    StringElement(string value): ValueContainer(value) {}

//    virtual bool isString() override { return true; }
//    virtual string asString() const override { return this->getValue(); }
//};

//class DoubleElement: public ValueContainer<double>, public Element {
//public:
//    DoubleElement(double value): ValueContainer(value) {}

//    virtual bool isDouble() override { return true; }
//    virtual double asDouble() const override { return this->getValue(); }
//};

//class IntegerElement: public ValueContainer<int>, public Element {
//public:
//    IntegerElement(int value): ValueContainer(value) {}

//    virtual bool isInteger() override { return true; }
//    virtual int asInteger() const override { return this->getValue(); }
//};

//class BoolElement: public ValueContainer<bool>, public Element {
//public:
//    BoolElement(bool value): ValueContainer(value) {}

//    virtual bool isBool() override { return true; }
//    virtual bool asBool() const override { return this->getValue(); }
//};

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

