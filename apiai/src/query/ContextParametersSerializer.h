#ifndef CONTEXTPARAMETERSSERIALIZER_H
#define CONTEXTPARAMETERSSERIALIZER_H

#include <string>
#include <map>

#include <apiai/query/response/Context.h>

class cJSON;

namespace ai{
    namespace query {
        namespace response {
            class ContextParametersSerializer
            {
            public:
                // TODO: Is it OK that the outgoing map is marked as 'const'.
                static const std::map<std::string, std::shared_ptr<Element>> serialize(cJSON *source);
            private:
                // TODO: It would be nice to return a smart pointer to a new element rather than an element itself. Too many copies happen.
                static std::shared_ptr<Element> serialize_element(cJSON *json_element);
                ContextParametersSerializer();
            };
        }
    }
}

#endif // CONTEXTPARAMETERSSERIALIZER_H
