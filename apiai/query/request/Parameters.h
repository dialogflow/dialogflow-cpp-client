#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <memory>
#include <vector>
#include <string>

namespace ai {
    namespace query {
        namespace request {
            class Parameters
            {
            public:
                Parameters(std::string sessionId,
                           bool resetContexts = false,
                           std::shared_ptr<std::string> timeZone = nullptr,
                           std::vector<std::string> contexts = {},
                           std::vector<std::string> entities = {});

            public:
                Parameters& setResetContexts(bool resetContexts);
                Parameters& setTimeZone(std::shared_ptr<std::string> timeZone);
                Parameters& addContext(std::string context);
                Parameters& addEntity(std::string entity);

            private:
                bool resetContexts;
                std::string sessionId;
                std::shared_ptr<std::string> timeZone;
                std::vector<std::string> contexts;
                std::vector<std::string> entities;
            };
        }
    }
}

#endif // PARAMETERS_H
