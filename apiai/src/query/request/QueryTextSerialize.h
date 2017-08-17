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

#ifndef QUERYTEXTSERIALIZE_H
#define QUERYTEXTSERIALIZE_H

#include <iostream>
#include "cJSON.h"

#include "QueryTextVisitor.h"

namespace ai {
    namespace query {
        namespace request {
            class QueryTextSerialize: public QueryTextVisitor
            {
            private:
                cJSON *query_element;
            public:

                QueryTextSerialize();

                virtual void visit(const QueryOne& ref) override;
                virtual void visit(const QueryMultipleStrings& ref) override;
                virtual void visit(const QueryMultipleVariants& ref) override;

                cJSON *getQuery_element() const;
            };
        }
    }
}

#endif // QUERYTEXTSERIALIZE_H
