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

#ifndef QUERYTEXT_H
#define QUERYTEXT_H

#include <stdexcept>

#include <memory>
#include <string>
#include <vector>

#include <apiai/exceptions/InvalidArgumentException.h>

namespace ai {
    namespace query {
        namespace request {
            class QueryTextVisitor;

            class QueryVariant {
            public:
                QueryVariant(const std::string text, const double confidence): text(text), confidence(confidence){}

                std::string getText() const { return text; }
                double getConfidence() const { return confidence; }

            private:
                std::string text;
                double confidence;
            };

            class QueryText {
            public:
                static const std::shared_ptr<QueryText> One(std::string query);
                static const std::shared_ptr<QueryText> Multiple(std::vector<std::string> query);
                static const std::shared_ptr<QueryText> Multiple(std::vector<QueryVariant> query);

            public:
                virtual void accept(QueryTextVisitor& serizalize) const = 0;
            };

            class QueryOne: public QueryText {
            public:
                virtual void accept(QueryTextVisitor& serizalize) const override;
            private:
                QueryOne(std::string query): query(query) {
                    if (query.size() == 0) {
                        throw InvalidArgumentException("Query cannot be empty.");
                    }
                }
                std::string query;

                friend class QueryText;
                friend class QueryTextSerialize;
            };

            class QueryMultipleStrings: public QueryText {
            public:
                virtual void accept(QueryTextVisitor& serizalize) const override;
            private:
                QueryMultipleStrings(std::vector<std::string> query): query(query) {
                    if (query.size() == 0) {
                        throw InvalidArgumentException("Query cannot be empty.");
                    }

                    for (auto& text: query) {
                        if (text.size() == 0) {
                            throw InvalidArgumentException("Query cannot be empty.");
                        }
                    }
                }
                std::vector<std::string> query;

                friend class QueryText;
                friend class QueryTextSerialize;
            };

            class QueryMultipleVariants: public QueryText {
            public:
                virtual void accept(QueryTextVisitor& serizalize) const override;
            private:
                QueryMultipleVariants(std::vector<QueryVariant> query): query(query)
                {
                    if (query.size() == 0) {
                        throw InvalidArgumentException("Query cannot be empty.");
                    }

                    for (auto& variant: query) {
                        if (variant.getText().size() == 0) {
                            throw InvalidArgumentException("Query cannot be empty.");
                        }
                    }
                }

                std::vector<QueryVariant> query;

                friend class QueryText;
                friend class QueryTextSerialize;
            };
        }
    }
}

#endif // QUERY_H
