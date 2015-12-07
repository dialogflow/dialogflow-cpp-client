#ifndef STREAM_THREAD_SAFETY_CHECK_H
#define STREAM_THREAD_SAFETY_CHECK_H

#include <io/StreamReader.h>
#include <io/StreamWriter.h>

namespace ai {
    namespace io {

        class Stream;

        class StreamThreadSafetyCheck {

            static ai::io::Stream &getStream();

            static ai::io::StreamReader getStreamReader();

            static ai::io::StreamWriter getStreamWriter();

            static void *write(void *arg);

            static void *read(void *arg);

            static void createDetachedThreads(void *(*startRoutine)(void *), unsigned int numberOfThreads);

            static void createDetachedWriter();

            static void createDetachedReader();

            static void waitUntilStreamIsEmptied();

            static void *readFile(void *arg);

            static void *writeFile(void *arg);

        public:

            static void startChecking();
        };
    }
}

#endif // STREAM_THREAD_SAFETY_CHECK_H
