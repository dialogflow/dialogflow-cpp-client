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

#include <apiai/query/response/Fulfillment.h>

#include <ostream>
#include <string>

using namespace std;
using namespace ai::query::response;

Fulfillment::Fulfillment(std::string speech): speech(speech)
{

}

std::string Fulfillment::getSpeech() const
{
    return speech;
}


Fulfillment::~Fulfillment() {}

namespace ai {
    namespace query {
        namespace response {
            std::ostream& operator << (std::ostream& os, const Fulfillment& fulfillment) {
                os << "Fulfillment:" << endl;
                os << "    " << "speech: " << fulfillment.speech;

                return os;
            }
        }
    }
}
