#ifndef CONTEXTPARAMETERSSERIALIZER_H
#define CONTEXTPARAMETERSSERIALIZER_H

#include "response/Context.h" // TODO: Shouldn't we use forward declaration instead?
#include "cJSON.h" // TODO: Shouldn't we use forward declaration instead?

#include <string>
#include <map>

namespace ai{
    namespace query {
        namespace response {
            class ContextParametersSerializer
            {
            public:
                // TODO: Is it OK that the outgoing map is marked as 'const'.
                static const std::map<std::string, Element> serialize(cJSON *source);
            private:
                // TODO: It would be nice to return a smart pointer to a new element rather than an element itself. Too many copies happen.
                static Element serialize_element(cJSON *json_element);
                ContextParametersSerializer();
            };
        }
    }
}

#endif // CONTEXTPARAMETERSSERIALIZER_H
