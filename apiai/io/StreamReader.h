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

            StreamReader &read(char *target, std::streamsize count);

            std::streamsize readsome(char *target, std::streamsize count);

        private:

            Stream &stream;
        };
    }
}

#endif // STREAM_READER_H
