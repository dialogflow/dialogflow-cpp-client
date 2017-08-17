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

#include <apiai/exceptions/JSONException.h>

#include <sstream>

namespace ai {

JSONException::JSONException(const std::string& message): std::runtime_error(message) {}

JSONException JSONException::MissingKey(const std::string &key)
{
    std::ostringstream reason;

    reason << "Missing key: ";
    reason << key;
    reason << ".";

    return JSONException(reason.str());
}

JSONException JSONException::TypeMismatch(const std::string &key, const std::string &expected_type)
{
    std::ostringstream reason;

    reason << "Type mismatch, key: ";
    reason << key;
    reason << ", expected type: ";
    reason << expected_type;
    reason << ".";

    return JSONException(reason.str());
}

}
