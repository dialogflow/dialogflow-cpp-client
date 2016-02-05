#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "Element.h"

namespace ai{
    namespace query {
        namespace response {
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
