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

        Stream &Stream::read(char *target, std::streamsize count) {
            this->mutex.lock();

            this->inout.read(target, count);

            this->mutex.unlock();

            return *this;
        }

        std::streamsize Stream::readsome(char *target, std::streamsize count) {
            this->mutex.lock();

            count = this->inout.readsome(target, count);

            this->mutex.unlock();

            return count;
        }
    }
}
