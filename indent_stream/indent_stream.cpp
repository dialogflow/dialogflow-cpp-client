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

#include "indent_stream.h"

using namespace ai::utils;

indent_stream::indent_stream(std::ostream &source_stream): source_stream(source_stream), std::ostream(this) {

}

int indent_stream::overflow(int c) {
    source_stream.put(c);

    if (c == '\n') {
        source_stream << "    ";
    }

    return 0;
}


