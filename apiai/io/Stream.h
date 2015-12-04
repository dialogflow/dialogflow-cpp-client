#ifndef STREAM_H
#define STREAM_H

#include <condition_variable>
#include <mutex>
#include <sstream>

namespace ai {
    namespace io {

        class Stream {
        public:

            bool isEmpty();

            bool isSealed();

            void seal();

            Stream &write(const char *source, std::streamsize count);

            std::streamsize read(char *target, std::streamsize count);

        private:

            bool unsafe_is_empty();

            bool unsafe_is_sealed() const;

            void unsafe_seal();

            bool unsafe_good() const;

            std::streampos unsafe_tellg();
            std::streampos unsafe_tellp();

            std::streamsize unsafe_in_avail();

            std::stringstream &unsafe_write(const char *source, std::streamsize count);
            std::stringstream &unsafe_read(char *target, std::streamsize count);

            void unsafe_flush();

            bool sealed = false;

            std::condition_variable condition_variable;
            std::mutex mutex;

            std::stringstream stringstream;
        };
    }
}

#endif // STREAM_H
