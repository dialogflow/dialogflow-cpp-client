#include <string>

#include "Stream.h"
#include "StreamWriter.h"

namespace ai {
    namespace io {

        StreamWriter::StreamWriter(Stream &stream) : stream_(stream) {
        }

        StreamWriter::StreamWriter(const StreamWriter &writer) : stream_(writer.stream_) {
        }

        StreamWriter &StreamWriter::write(const std::string &source) {
            return this->write(source.c_str(), source.size());
        }

        StreamWriter &StreamWriter::write(const char *source, std::streamsize count) {
            this->stringstream_.write(source, count);
            this->stringstream_.flush();

            return *this;
        }

        bool StreamWriter::sealed() {
            return this->stream_.sealed();
        }

        void StreamWriter::sealed(bool sealed) {
            this->stream_.sealed(sealed);
        }

        std::string StreamWriter::str() {
            return this->stream_.str();
        }

        void StreamWriter::str(const std::string &string) {
            this->stream_.str(string);
        }

        void StreamWriter::flush() {
            const std::streampos gpos = this->stringstream_.tellg(); // input
            const std::streampos ppos = this->stringstream_.tellp(); // output
            if (gpos < ppos) {
                const std::streamsize size = ppos - gpos;
                char *characters = new char[size];
                this->stringstream_.read(characters, size);
                this->stream_.write(characters, size);
                delete [] characters;
                characters = NULL;
            }
        }
    }
}
