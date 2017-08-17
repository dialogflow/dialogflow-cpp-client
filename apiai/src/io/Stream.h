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

#ifndef STREAM_H
#define STREAM_H

#include <condition_variable>
#include <mutex>
#include <sstream>

namespace ai {
    namespace io {

        class Stream {
        public:

            bool atEnd();

            bool sealed();

            void sealed(bool sealed);

            std::string str();

            void str(const std::string &string);

            Stream &write(const std::string &source);

            Stream &write(const char *source, std::streamsize count);

            std::streamsize read(char *target, std::streamsize count);

            void swap(Stream &stream);

            void reset();

        private:

            bool unsafeAtEnd();

            bool unsafeSealed() const;

            void unsafeSealed(bool sealed);

            bool unsafeGood() const;

            std::string unsafeStr() const;

            void unsafeStr(const std::string &string);

            std::streampos unsafeTellg();
            void unsafeSeekg(std::streampos pos);

            std::streampos unsafeTellp();
            void unsafeSeekp(std::streampos pos);

            std::streamsize unsafeInAvail();

            std::stringstream &unsafeWrite(const char *source, std::streamsize count);
            std::stringstream &unsafeRead(char *target, std::streamsize count);

            void unsafeFlush();

            void unsafeSwap(Stream &stream);

            void unsafeReset();

            bool sealed_ = false;

            std::condition_variable conditionVariable_;
            std::mutex mutex_;

            std::stringstream stringstream_;
        };
    }
}

#endif // STREAM_H
