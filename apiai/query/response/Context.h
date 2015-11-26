#ifndef CONTEXT_H
#define CONTEXT_H

#include "../../JSON/JSONException.h"

#include <string>
#include <map>
#include <vector>

namespace ai{
    namespace query {
        namespace response {
            class Element {
            public:
                virtual bool isObject();
                virtual bool isNumber();
                virtual bool isInteger();
                virtual bool isArray();
                virtual bool isBool();
                virtual bool isString();

                virtual std::map<std::string, Element> asObject() const;
                virtual double asDouble() const;
                virtual int asInteger() const;
                virtual std::vector<Element> asArray() const;
                virtual bool asBool() const;
                virtual std::string asString() const;
            };

            template <typename T>
            class ValueContainer {
            public:
                ValueContainer(T value):value(value) {}

                T getValue() const
                {
                    return value;
                }
            private:
                T value;
            };

            class ObjectElement: public ValueContainer<std::map<std::string, Element>>, public Element{
            public:
                ObjectElement(std::map<std::string, Element> value): ValueContainer(value) {}

                virtual bool isObject() override { return true; }
                virtual std::map<std::string, Element> asObject() const override { return this->getValue(); }
            };

            class ArrayElement: public ValueContainer<std::vector<Element>>, public Element {
            public:
                ArrayElement(std::vector<Element> value): ValueContainer(value) {}

                virtual bool isArray() override { return true; }
                virtual std::vector<Element> asArray() const override { return this->getValue(); }
            };

            class StringElement: public ValueContainer<std::string>, public Element {
            public:
                StringElement(std::string value): ValueContainer(value) {}

                virtual bool isString() override { return true; }
                virtual std::string asString() const override { return this->getValue(); }
            };

            class NumberElement: public ValueContainer<double>, public Element {
            public:
                NumberElement(double value): ValueContainer(value) {}

                virtual bool isNumber() override { return true; }
                virtual double asDouble() const override { return this->getValue(); }
                virtual int asInteger() const override { return (int)this->getValue(); }
            };

            class BoolElement: public ValueContainer<bool>, public Element {
            public:
                BoolElement(bool value): ValueContainer(value) {}

                virtual bool isBool() override { return true; }
                virtual bool asBool() const override { return this->getValue(); }
            };

            class Context
            {
            public:
                Context(std::string name, int lifespan, std::map<std::string, Element> parameters);

                int getLifespan() const;
                std::string getName() const;
                std::map<std::string, Element> getParameters() const;
            private:
                const std::string name;
                const int lifespan;
                const std::map<std::string, Element> parameters;
            };
        }
    }
}

#endif // CONTEXT_H
