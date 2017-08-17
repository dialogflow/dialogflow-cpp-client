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

#ifndef STREAM_THREAD_SAFETY_CHECK_H
#define STREAM_THREAD_SAFETY_CHECK_H

#include <io/StreamReader.h>
#include <io/StreamWriter.h>

namespace ai {
    namespace io {

        class Stream;

        class StreamThreadSafetyCheck {

            static ai::io::Stream &getStream();

            static ai::io::StreamReader getStreamReader();

            static ai::io::StreamWriter getStreamWriter();

            static void *write(void *arg);

            static void *read(void *arg);

            static void createDetachedThreads(void *(*startRoutine)(void *), unsigned int numberOfThreads);

            static void createDetachedWriter();

            static void createDetachedReader();

            static void waitUntilStreamIsEmptied();

            static void *readFile(void *arg);

            static void *writeFile(void *arg);

        public:

            static void startChecking();
        };
    }
}

#endif // STREAM_THREAD_SAFETY_CHECK_H
