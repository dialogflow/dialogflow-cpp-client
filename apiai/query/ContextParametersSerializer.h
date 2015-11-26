#ifndef CONTEXTPARAMETERSSERIALIZER_H
#define CONTEXTPARAMETERSSERIALIZER_H

#include "response/Context.h"
#include "cJSON.h"

#include <string>
#include <map>

namespace ai{
    namespace query {
        namespace response {
            class ContextParametersSerializer
            {
            public:
                static const std::map<std::string, Element> serialize(cJSON *source);
            private:
                static Element serialize_element(cJSON *json_element);
                ContextParametersSerializer();
            };
        }
    }
}

#endif // CONTEXTPARAMETERSSERIALIZER_H
