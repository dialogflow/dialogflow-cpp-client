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

            void flush();

        private:

            Stream &stream;
            std::stringstream buffer;
        };
    }
}

#endif // STREAM_WRITER_H
