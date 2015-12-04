#include "Stream.h"
#include "StreamReader.h"

namespace ai {
    namespace io {

        StreamReader::StreamReader(Stream &stream) : stream(stream) {
        }

        StreamReader::StreamReader(const StreamReader &reader) : stream(reader.stream) {
        }

        std::streamsize StreamReader::read(char *target, std::streamsize count) {
            return this->stream.read(target, count);
        }

        bool StreamReader::isAtEnd() {
            return this->stream.isAtEnd();
        }
    }
}
