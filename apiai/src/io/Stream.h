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
