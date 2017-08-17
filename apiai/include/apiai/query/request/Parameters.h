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

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <memory>
#include <vector>
#include <string>

#include "Entity.h"
#include "RequestContext.h"

namespace ai {
    namespace query {
        namespace request {
            class Parameters
            {
            public:
                Parameters(std::string sessionId,
                           bool resetContexts = false,
                           std::shared_ptr<std::string> timeZone = nullptr,
                           std::vector<RequestContext> contexts = {},
                           std::vector<Entity> entities = {});

            public:
                Parameters& setResetContexts(bool resetContexts);
                Parameters& setTimeZone(std::shared_ptr<std::string> timeZone);
                Parameters& addContext(RequestContext context);
                Parameters& addEntity(Entity entity);

                bool getResetContexts() const;
                std::string getSessionId() const;
                std::shared_ptr<std::string> getTimeZone() const;
                std::vector<RequestContext> getContexts() const;
                std::vector<Entity> getEntities() const;

            private:
                bool resetContexts;
                std::string sessionId;
                std::shared_ptr<std::string> timeZone;
                std::vector<RequestContext> contexts;
                std::vector<Entity> entities;
            };
        }
    }
}

#endif // PARAMETERS_H
