#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace ai{
    namespace query {
        namespace response {
            class Element {
            public:
                virtual bool isObject() const;
                virtual bool isNumber() const;
                virtual bool isArray() const;
                virtual bool isBool() const;
                virtual bool isString() const;

                virtual std::map<std::string, std::shared_ptr<Element>> asObject() const;
                virtual double asDouble() const;
                virtual int asInteger() const;
                virtual std::vector<std::shared_ptr<Element>> asArray() const;
                virtual bool asBool() const;
                virtual std::string asString() const;

                friend std::ostream& operator << (std::ostream& os, const Element& element);
            };

            std::ostream& operator << (std::ostream& os, const Element& element);

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

            class ObjectElement: public ValueContainer<std::map<std::string, std::shared_ptr<Element>>>, public Element{
            public:
                ObjectElement(std::map<std::string, std::shared_ptr<Element>> value): ValueContainer(value) {}

                virtual bool isObject() const override { return true; }
                virtual std::map<std::string, std::shared_ptr<Element>> asObject() const override { return this->getValue(); }
            };

            class ArrayElement: public ValueContainer<std::vector<std::shared_ptr<Element>>>, public Element {
            public:
                ArrayElement(std::vector<std::shared_ptr<Element>> value): ValueContainer(value) {}

                virtual bool isArray() const override { return true; }
                virtual std::vector<std::shared_ptr<Element>> asArray() const override { return this->getValue(); }
            };

            class StringElement: public ValueContainer<std::string>, public Element {
            public:
                StringElement(std::string value): ValueContainer(value) {}

                virtual bool isString() const override { return true; }
                virtual std::string asString() const override { return this->getValue(); }
            };

            class NumberElement: public ValueContainer<double>, public Element {
            public:
                NumberElement(double value): ValueContainer(value) {}

                virtual bool isNumber() const override { return true; }
                virtual double asDouble() const override { return this->getValue(); }
                virtual int asInteger() const override { return (int)this->getValue(); }
            };

            class BoolElement: public ValueContainer<bool>, public Element {
            public:
                BoolElement(bool value): ValueContainer(value) {}

                virtual bool isBool() const override { return true; }
                virtual bool asBool() const override { return this->getValue(); }
            };

            class Context
            {
            public:
                Context(std::string name, int lifespan, std::map<std::string, std::shared_ptr<Element>> parameters);

                int getLifespan() const;
                std::string getName() const;
                std::map<std::string, std::shared_ptr<Element>> getParameters() const;
            private:
                const std::string name;
                const int lifespan;
                const std::map<std::string, std::shared_ptr<Element>> parameters;

                friend std::ostream& operator << (std::ostream& os, const Context& context);
            };

            std::ostream& operator << (std::ostream& os, const Context& context);
        }
    }
}

#endif // CONTEXT_H
