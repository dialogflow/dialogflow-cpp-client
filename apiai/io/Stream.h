#ifndef STREAM_H
#define STREAM_H

#include <condition_variable>
#include <mutex>
#include <sstream>

namespace ai {
    namespace io {

        class Stream {
        public:

            bool isAtEnd();

            bool isSealed();

            void seal();

            Stream &write(const char *source, std::streamsize count);

            std::streamsize read(char *target, std::streamsize count);

        private:

            bool unsafeIsAtEnd();

            bool unsafeIsSealed() const;

            void unsafeSeal();

            bool unsafeGood() const;

            std::streampos unsafeTellg();
            std::streampos unsafeTellp();

            std::streamsize unsafeInAvail();

            std::stringstream &unsafeWrite(const char *source, std::streamsize count);
            std::stringstream &unsafeRead(char *target, std::streamsize count);

            void unsafeFlush();

            bool sealed = false;

            std::condition_variable conditionVariable;
            std::mutex mutex;

            std::stringstream stringstream;
        };
    }
}

#endif // STREAM_H
