#include "Stream.h"
#include "StreamReader.h"

namespace ai {
    namespace io {

        StreamReader::StreamReader(Stream &stream) : stream(stream) {
        }

        StreamReader::StreamReader(const StreamReader &reader) : stream(reader.stream) {
        }

        StreamReader &StreamReader::read(char *target, std::streamsize count) {
            this->stream.read(target, count);

            return *this;
        }

        std::streamsize StreamReader::readsome(char *target, std::streamsize count) {
            return this->stream.readsome(target, count);
        }
    }
}
