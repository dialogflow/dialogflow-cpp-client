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

#include <apiai/query/response/Metadata.h>

#include <memory>
#include <string>
#include <ostream>

using namespace std;
using namespace ai::query::response;

Metadata::Metadata(shared_ptr<string> intentId,
                   shared_ptr<string> intentName):
    intentId(intentId), intentName(intentName)
{

}

Metadata::Metadata(): intentId(nullptr), intentName(nullptr) {

}

shared_ptr<string> Metadata::getIntentId() const
{
    return intentId;
}

shared_ptr<string> Metadata::getIntentName() const
{
    return intentName;
}

Metadata::~Metadata()
{

}

namespace ai {
    namespace query {
        namespace response {
            std::ostream& operator << (std::ostream& os, const Metadata& metadata) {
                os << "Metadata: " << endl;

                os << "    " << "intentId: ";

                if (metadata.intentId.get()) {
                    os << *metadata.intentId.get();
                } else {
                    os << "NULL";
                }

                os << endl;

                os << "    " << "intentName: ";

                if (metadata.intentName.get()) {
                    os << *metadata.intentName.get();
                } else {
                    os << "NULL";
                }

                os << endl;

                return os;
            }
        }
    }
}
