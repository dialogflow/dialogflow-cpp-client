#ifndef CONTEXT_H
#define CONTEXT_H

#include "../JSON/JSONException.h"

#include <string>
#include <map>
#include <vector>

namespace ai{
    namespace query {
        namespace response {
            class Element {
            public:
                virtual bool isObject();
                virtual bool isDouble();
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
