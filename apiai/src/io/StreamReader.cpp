#include "Stream.h"
#include "StreamReader.h"

namespace ai {
    namespace io {

        StreamReader::StreamReader(Stream &stream) : stream_(stream) {
        }

        StreamReader::StreamReader(const StreamReader &reader) : stream_(reader.stream_) {
        }

        std::streamsize StreamReader::read(char *target, std::streamsize count) {
            return this->stream_.read(target, count);
        }

        bool StreamReader::atEnd() {
            return this->stream_.atEnd();
        }

        bool StreamReader::sealed() {
            return this->stream_.sealed();
        }

        std::string StreamReader::str() {
            return this->stream_.str();
        }
    }
}
