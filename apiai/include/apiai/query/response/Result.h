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
 
#ifndef RESULT_H
#define RESULT_H

#include "Metadata.h" // TODO: Shouldn't we use forward declaration instead?
#include "Context.h" // TODO: Shouldn't we use forward declaration instead?

#include <vector>

namespace ai {
    namespace query {
        namespace response {
            class Fulfillment;
        }
        namespace request {
            class QueryRequest;
        }

        namespace response {
            class Result {
            public:
                std::string getSource() const;
                std::string getResolvedQuery() const;
                std::shared_ptr<std::string> getAction() const;
                std::shared_ptr<Fulfillment> getFulfillment() const;
                Metadata getMetadata() const;
                std::map<std::string, std::shared_ptr<Element>> getParameters() const;
                std::vector<Context> getContexts() const;

                virtual ~Result();

                friend std::ostream& operator << (std::ostream& os, const Result& result);

            private:
                const std::string source;
                const std::string resolvedQuery;
                const std::shared_ptr<std::string> action;
                const std::shared_ptr<Fulfillment> fulfillment;
                const Metadata metadata;
                const std::map<std::string, std::shared_ptr<Element>> parameters;
                const std::vector<Context> contexts;

                Result(const std::string source,
                       const std::string resolvedQuery,
                       const std::shared_ptr<std::string> action,
                       const std::shared_ptr<Fulfillment> fulfillment,
                       const Metadata metadata,
                       std::map<std::string, std::shared_ptr<Element>> parameters,
                       const std::vector<ai::query::response::Context> contexts);

                friend class ai::query::request::QueryRequest;
            };

            std::ostream& operator << (std::ostream& os, const Result& result);
        }
    }
}

#endif // RESULT_H
