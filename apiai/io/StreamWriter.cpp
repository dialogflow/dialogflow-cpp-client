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
            this->stringstream.write(source, count);
            this->stringstream.flush();

            return *this;
        }

        bool StreamWriter::isSealed() {
            return this->stream.isSealed();
        }

        void StreamWriter::seal() {
            this->stream.seal();
        }

        void StreamWriter::flush() {
            const std::streampos gpos = this->stringstream.tellg(); // input
            const std::streampos ppos = this->stringstream.tellp(); // output
            if (gpos < ppos) {
                const std::streamsize size = ppos - gpos;
                char *characters = new char[size];
                this->stringstream.read(characters, size);
                this->stream.write(characters, size);
                delete [] characters;
                characters = NULL;
            }
        }
    }
}
