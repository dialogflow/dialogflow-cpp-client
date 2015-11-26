#ifndef INDENT_STREAM_H
#define INDENT_STREAM_H

#include <ostream>

namespace ai{
    namespace utils {
        class indent_stream: public std::ostream, public std::streambuf {
        public:
            indent_stream(std::ostream& source_stream);
            int overflow(int c) override;
        private:
            std::ostream& source_stream;
        };
    }
}

#endif // INDENT_STREAM_H
