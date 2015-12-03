#include <iostream>
#include <mutex>
#include <pthread.h>
#include <string>
#include <sstream>

#include "Stream.h"
#include "ThreadSafetyCheck.h"

namespace ai {
    namespace io {

        ai::io::Stream &ThreadSafetyCheck::getStream() {
            static ai::io::Stream stream;
            return stream;
        }

        ai::io::StreamReader ThreadSafetyCheck::getStreamReader() {
            return getStream();
        }

        ai::io::StreamWriter ThreadSafetyCheck::getStreamWriter() {
            return getStream();
        }

        static std::mutex __mutex_print;
        static std::mutex __mutex_increase;

        void *ThreadSafetyCheck::write(void *arg) {
            int id = (arg == NULL) ? 0 : *(int *)arg;
            static unsigned long long counter = 0ll;
            ai::io::StreamWriter writer = getStreamWriter();
            while (true) {
                usleep(500000);

                __mutex_increase.lock();
                std::stringstream output;
                output << counter++ << " ";
                __mutex_increase.unlock();

                __mutex_print.lock();
                std::cout << "writer (" << id << "): " << output.str() << std::endl;
                __mutex_print.unlock();

                std::string stringToWrite = output.str();
                writer.write(stringToWrite.c_str(), stringToWrite.size());
                writer.flush();
            }

            return NULL;
        }

        void *ThreadSafetyCheck::read(void *arg) {
            static const unsigned int sizeOfBuffer = 2048;
            int id = (arg == NULL) ? 0 : *(int *)arg;
            ai::io::StreamReader reader = getStreamReader();
            while (true) {
                usleep(1000000);

                char *buffer = new char[sizeOfBuffer];
                const int count = reader.readsome(buffer, sizeOfBuffer);

                if (count > 0) {
                    std::string message{""};
                    message.assign(buffer, count);

                    __mutex_print.lock();
                    std::cout << "        reader (" << id << "): " << message << std::endl;
                    __mutex_print.unlock();
                }

                delete [] buffer;
                buffer = NULL;
            }

            return NULL;
        }

        void ThreadSafetyCheck::createDetachedWriters(unsigned int numberOfWriters) {
            pthread_t writer;
            for (unsigned int index = 0; index < numberOfWriters; ++index) {
                if (pthread_create(&writer, NULL, write, (void *)&index) == 0) {
                    pthread_detach(writer);
                }
                else {
                    abort();
                }
            }
        }

        void ThreadSafetyCheck::createDetachedReaders(unsigned int numberOfReaders) {
            pthread_t reader;
            for (unsigned int index = 0; index < numberOfReaders; ++index) {
                if (pthread_create(&reader, NULL, read, (void *)&index) == 0) {
                    pthread_detach(reader);
                }
                else {
                    abort();
                }
            }
        }

        void ThreadSafetyCheck::waitInfinitely() {
            while (true) {
                sleep(5);
            }
        }

        void ThreadSafetyCheck::check() {
            createDetachedWriters(11);
            createDetachedReaders(7);
            waitInfinitely();
        }
    }
}
