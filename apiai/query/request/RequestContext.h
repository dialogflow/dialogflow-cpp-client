#ifndef REQUESTCONTEXT_H
#define REQUESTCONTEXT_H

#include <string>
#include <map>

namespace ai{
    namespace query {
        namespace request {
            class RequestContext
            {
            public:
                RequestContext(std::string name, int lifespan = -1, std::map<std::string, std::string> parameters = {});

                RequestContext& addParameter(std::string name, std::string value);

                const std::string& getName() const;
                void setName(const std::string& name);

                const std::map<std::string, std::string>& getParameters() const;
                void setParameters(const std::map<std::string, std::string>& parameters);

                const int& getLifespan() const;
                void setLifespan(const int& lifespan);
            private:
                int lifespan;
                std::string name;
                std::map<std::string, std::string> parameters;
            };
        }
    }
}

#endif // REQUESTCONTEXT_H
