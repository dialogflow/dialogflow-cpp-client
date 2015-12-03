#include <string>

#include "Stream.h"
#include "StreamWriter.h"

namespace ai {
    namespace io {

        StreamWriter::StreamWriter(Stream &stream) : stream(stream) {
        }

        StreamWriter::StreamWriter(const StreamWriter &writer) : stream(writer.stream) {
        }

        StreamWriter &StreamWriter::write(const char *source, std::streamsize count) {
            this->buffer.write(source, count);

            return *this;
        }

        void StreamWriter::flush() {
            std::string bufferedString = this->buffer.str();
            this->stream.write(bufferedString.c_str(), bufferedString.size());
            std::stringstream().swap(this->buffer);
        }
    }
}
