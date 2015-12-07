#ifndef STREAM_READER_H
#define STREAM_READER_H

#include <sstream>

namespace ai {
    namespace io {

        class Stream;

        class StreamReader {
        public:

            StreamReader(Stream &stream);

            StreamReader(const StreamReader &reader);

            std::streamsize read(char *target, std::streamsize count);

            bool atEnd();

            bool sealed();

            std::string str();

        private:

            Stream &stream_;
        };
    }
}

#endif // STREAM_READER_H
