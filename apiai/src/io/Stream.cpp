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

#include "Stream.h"

#include <apiai/Types.h>

using namespace std;

namespace ai {
    namespace io {

        ///
        /// Thread-safe methods
        ///

        bool Stream::atEnd() {
            std::unique_lock<std::mutex> lock(this->mutex_);
            return this->unsafeAtEnd();
        }

        bool Stream::sealed() {
            std::unique_lock<std::mutex> lock(this->mutex_);
            return this->unsafeSealed();
        }

        void Stream::sealed(bool sealed) {
            std::unique_lock<std::mutex> lock(this->mutex_);
            this->unsafeSealed(sealed);
        }

        std::string Stream::str() {
            std::unique_lock<std::mutex> lock(this->mutex_);
            return this->unsafeStr();
        }

        void Stream::str(const std::string &string) {
            std::unique_lock<std::mutex> lock(this->mutex_);
            this->unsafeStr(string);
        }

        Stream &Stream::write(const std::string &source) {
            return this->write(source.c_str(), source.size());
        }

        Stream &Stream::write(const char *source, std::streamsize count) {
            {
                std::unique_lock<std::mutex> lock(this->mutex_);
                if (this->unsafeSealed()) {
                    return *this;
                }

                this->unsafeWrite(source, count);
                this->unsafeFlush();
            }
            this->conditionVariable_.notify_all();

            return *this;
        }

        std::streamsize Stream::read(char *target, std::streamsize count) {
            std::streamsize read = 0;
            {
                std::unique_lock<std::mutex> lock(this->mutex_);
                if (this->unsafeGood()) {
                    if (this->unsafeAtEnd()) {
                        return read;
                    }

                    this->conditionVariable_.wait(lock, [this]{
                        return (this->unsafeInAvail() > 0);
                    });

                    const std::streamsize inAvail = this->unsafeInAvail();
                    if (inAvail > 0) {
                        read = std::min(inAvail, count);
                        this->unsafeRead(target, read);
                    }
                }
            }

            return read;
        }

        void Stream::swap(Stream &stream) {
            std::unique_lock<std::mutex> lock(this->mutex_);
            this->unsafeSwap(stream);
        }

        void Stream::reset() {
            std::unique_lock<std::mutex> lock(this->mutex_);
            this->unsafeReset();
        }

        ///
        /// Thread-unsafe methods
        ///

        bool Stream::unsafeAtEnd() {
            return (this->unsafeSealed()) && (this->unsafeInAvail() == 0);
        }

        bool Stream::unsafeSealed() const {
            return this->sealed_;
        }

        void Stream::unsafeSealed(bool sealed) {
            this->sealed_ = sealed;
        }

        bool Stream::unsafeGood() const {
            return this->stringstream_.good();
        }

        std::string Stream::unsafeStr() const {
            return this->stringstream_.str();
        }

        void Stream::unsafeStr(const std::string &string) {
            this->stringstream_.str(string);
            this->unsafeSeekp(string.length());
            this->unsafeSeekg(0);
        }

        std::streampos Stream::unsafeTellg() {
            return this->stringstream_.tellg();
        }

        void Stream::unsafeSeekg(std::streampos pos) {
            this->stringstream_.seekg(pos);
        }

        std::streampos Stream::unsafeTellp() {
            return this->stringstream_.tellp();
        }

        void Stream::unsafeSeekp(std::streampos pos) {
            this->stringstream_.seekp(pos);
        }

        std::streamsize Stream::unsafeInAvail() {
            const std::streampos gpos = this->unsafeTellg(); // input
            const std::streampos ppos = this->unsafeTellp(); // output

            return (gpos < ppos) ? (ppos - gpos) : 0;
        }

        std::stringstream &Stream::unsafeWrite(const char *source, std::streamsize count) {
            this->stringstream_.write(source, count);

            return this->stringstream_;
        }

        std::stringstream &Stream::unsafeRead(char *target, std::streamsize count) {
            this->stringstream_.read(target, count);

            return this->stringstream_;
        }

        void Stream::unsafeFlush() {
            this->stringstream_.flush();
        }

        void Stream::unsafeSwap(Stream &stream) {
            #if GCC_COMPILER
                #if GCC_VERSION >= 50000
                    this->stringstream_.swap(stream.stringstream_);
                #else
                    auto tmp = string(stringstream_.str());
                    stringstream_.str(stream.stringstream_.str());
                    stream.stringstream_.str(tmp.c_str());
                #endif
            #else
                this->stringstream_.swap(stream.stringstream_);
            #endif

            this->sealed(stream.sealed());
        }

        void Stream::unsafeReset() {
            Stream stream;
            this->unsafeSwap(stream);
        }
    }
}
