#ifndef STREAM_WRITER_H
#define STREAM_WRITER_H

#include <sstream>

namespace ai {
    namespace io {

        class Stream;

        class StreamWriter {
        public:

            StreamWriter(Stream &stream);

            StreamWriter(const StreamWriter &writer);

            StreamWriter &write(const char *source, std::streamsize count);

            bool isSealed();

            void seal();

            void flush();

        private:

            Stream &stream;
            std::stringstream stringstream;
        };
    }
}

#endif // STREAM_WRITER_H
