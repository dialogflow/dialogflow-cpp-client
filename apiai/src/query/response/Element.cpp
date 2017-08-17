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

#include "apiai/query/response/Element.h"
#include "apiai/exceptions/JSONException.h"

using namespace std;
using namespace ai::query::response;

bool Element::isObject()    const   { return false; }
bool Element::isNumber()    const   { return false; }
bool Element::isArray()     const   { return false; }
bool Element::isBool()      const   { return false; }
bool Element::isString()    const   { return false; }

map<string, shared_ptr<Element>>    Element::asObject()     const   { throw JSONException("Cannot cast value to Object type."); }
double                              Element::asDouble()     const   { throw JSONException("Cannot cast value to Double type."); }
int                                 Element::asInteger()    const   { throw JSONException("Cannot cast value to Integer type."); }
vector<shared_ptr<Element>>         Element::asArray()      const   { throw JSONException("Cannot cast value to Array type."); }
bool                                Element::asBool()       const   { throw JSONException("Cannot cast value to Bool type."); }
string                              Element::asString()     const   { throw JSONException("Cannot cast value to String type."); }

// Object element

ObjectElement::ObjectElement(std::map<std::string, std::shared_ptr<Element>> value): ValueContainer(value)
{

}

bool ObjectElement::isObject() const
{
    return true;
}

std::map<std::string, std::shared_ptr<Element>> ObjectElement::asObject() const
{
    return this->getValue();
}

// Array Element

ArrayElement::ArrayElement(std::vector<std::shared_ptr<Element>> value): ValueContainer(value)
{

}

bool ArrayElement::isArray() const
{
    return true;
}

std::vector<std::shared_ptr<Element>> ArrayElement::asArray() const
{
    return this->getValue();
}

// String element

StringElement::StringElement(std::string value): ValueContainer(value)
{

}

bool StringElement::isString() const
{
    return true;
}

std::string StringElement::asString() const
{
    return this->getValue();
}

// Number element

NumberElement::NumberElement(double value): ValueContainer(value) {}

bool NumberElement::isNumber() const
{
    return true;
}

double NumberElement::asDouble() const
{
    return this->getValue();
}

int NumberElement::asInteger() const
{
    return (int)this->getValue();
}

// Bool element

BoolElement::BoolElement(bool value): ValueContainer(value)
{

}

bool BoolElement::isBool() const
{
    return true;
}

bool BoolElement::asBool() const
{
    return this->getValue();
}
