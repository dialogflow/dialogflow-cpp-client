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
