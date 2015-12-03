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
            this->buffer.flush();

            return *this;
        }

        void StreamWriter::flush() {
            const std::streampos gpos = this->buffer.tellg(); // input
            const std::streampos ppos = this->buffer.tellp(); // output
            if (gpos < ppos) {
                const std::streamsize size = ppos - gpos;
                char *characters = new char[size];
                this->buffer.read(characters, size);
                this->stream.write(characters, size);
                delete [] characters;
                characters = NULL;
            }
        }
    }
}
