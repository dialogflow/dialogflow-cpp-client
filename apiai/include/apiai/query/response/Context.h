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
