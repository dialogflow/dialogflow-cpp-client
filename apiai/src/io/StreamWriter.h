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

            StreamWriter &write(const std::string &source);

            StreamWriter &write(const char *source, std::streamsize count);

            bool sealed();

            void sealed(bool sealed);

            std::string str();

            void str(const std::string &string);

            void flush();

        private:

            Stream &stream_;
            std::stringstream stringstream_;
        };
    }
}

#endif // STREAM_WRITER_H
