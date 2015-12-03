#include "Stream.h"

namespace ai {
    namespace io {

        Stream &Stream::write(const char *source, std::streamsize count) {
            this->mutex.lock();

            if (this->inout.eof()) {
                this->inout.clear();
            }
            this->inout.write(source, count);
            this->inout.flush();

            this->mutex.unlock();

            return *this;
        }

        std::streamsize Stream::read(char *target, std::streamsize count) {
            this->mutex.lock();

            std::streamsize read = 0;
            const std::streampos gpos = this->inout.tellg(); // input
            const std::streampos ppos = this->inout.tellp(); // output
            if (gpos < ppos) {
                const std::streamsize available = ppos - gpos;
                read = std::min(available, count);
                this->inout.read(target, read);
            }

            this->mutex.unlock();

            return read;
        }
    }
}
