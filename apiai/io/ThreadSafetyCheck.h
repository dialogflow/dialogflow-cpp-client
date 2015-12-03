#ifndef THREAD_SAFETY_CHECK_H
#define THREAD_SAFETY_CHECK_H

#include "StreamReader.h"
#include "StreamWriter.h"

namespace ai {
    namespace io {

        class Stream;

        class ThreadSafetyCheck {

            static ai::io::Stream &getStream();

            static ai::io::StreamReader getStreamReader();

            static ai::io::StreamWriter getStreamWriter();

            static void *write(void *arg);

            static void *read(void *arg);

            static void createDetachedWriters(unsigned int numberOfWriters);

            static void createDetachedReaders(unsigned int numberOfReaders);

            static void waitInfinitely();

        public:

            static void check();
        };
    }
}

#endif // THREAD_SAFETY_CHECK_H
