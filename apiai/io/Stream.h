#ifndef STREAM_H
#define STREAM_H

#include <mutex>
#include <sstream>

namespace ai {
    namespace io {

        class Stream {
        public:
            Stream &write(const char *source, std::streamsize count);

            std::streamsize read(char *target, std::streamsize count);

        private:

            std::mutex mutex;
            std::stringstream inout;
        };
    }
}

#endif // STREAM_H
