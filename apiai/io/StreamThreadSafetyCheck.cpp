#include <condition_variable>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <string>
#include <sstream>

#include "Stream.h"
#include "StreamThreadSafetyCheck.h"

namespace ai {
    namespace io {

        ai::io::Stream &StreamThreadSafetyCheck::getStream() {
            static ai::io::Stream stream;
            return stream;
        }

        ai::io::StreamReader StreamThreadSafetyCheck::getStreamReader() {
            return getStream();
        }

        ai::io::StreamWriter StreamThreadSafetyCheck::getStreamWriter() {
            return getStream();
        }

        static std::mutex __mutex_print;
        static std::mutex __mutex_increase;

        static std::condition_variable __condition_variable_stream_emptiness;
        static std::mutex __mutex_stream_emptiness;

        static unsigned long long counter = 0ll;

        static unsigned long long getCounter() {
            std::unique_lock<std::mutex> lock(__mutex_increase);
            return counter;
        }

        static unsigned long long increaseCounter() {
            std::unique_lock<std::mutex> lock(__mutex_increase);
            return ++counter;
        }

        void *StreamThreadSafetyCheck::write(void *arg) {
            int id = (arg == NULL) ? 0 : *(int *)arg;
            ai::io::StreamWriter writer = getStreamWriter();
            while (getCounter() < 100) {
                std::stringstream output;
                output << increaseCounter() << " ";

                __mutex_print.lock();
                std::cout << "writer (" << id << "): " << output.str() << std::endl;
                __mutex_print.unlock();

                std::string stringToWrite = output.str();
                writer.write(stringToWrite.c_str(), stringToWrite.size());
                writer.flush();
            }
            writer.seal();

            return NULL;
        }

        void *StreamThreadSafetyCheck::read(void *arg) {
            std::unique_lock<std::mutex> lock(__mutex_stream_emptiness);

            static const unsigned int sizeOfBuffer = 2048;
            int id = (arg == NULL) ? 0 : *(int *)arg;
            ai::io::StreamReader reader = getStreamReader();
            while (true) {
                char *buffer = new char[sizeOfBuffer];
                const int count = reader.read(buffer, sizeOfBuffer);

                if (count > 0) {
                    std::string message{""};
                    message.assign(buffer, count);

                    __mutex_print.lock();
                    std::cout << "        reader (" << id << "): " << message << std::endl;
                    __mutex_print.unlock();
                }
                else {
                    __mutex_print.lock();
                    std::cout << "The stream has been emptied." << std::endl;
                    __mutex_print.unlock();
                }

                delete [] buffer;
                buffer = NULL;

                if (count == 0) {
                    break;
                }
            }

            lock.unlock();
            __condition_variable_stream_emptiness.notify_one();

            return NULL;
        }

        void StreamThreadSafetyCheck::createDetachedThreads(void *(*startRoutine)(void *), unsigned int numberOfThreads) {
            pthread_t thread;
            for (unsigned int index = 0; index < numberOfThreads; ++index) {
                if (pthread_create(&thread, NULL, startRoutine, (void *)&index) == 0) {
                    pthread_detach(thread);
                }
                else {
                    abort();
                }
            }
        }

        void StreamThreadSafetyCheck::createDetachedWriters(unsigned int numberOfWriters) {
            createDetachedThreads(write, numberOfWriters);
        }

        void StreamThreadSafetyCheck::createDetachedReaders(unsigned int numberOfReaders) {
            createDetachedThreads(read, numberOfReaders);
        }

        void StreamThreadSafetyCheck::waitUntilStreamIsEmptied() {
            std::unique_lock<std::mutex> lock(__mutex_stream_emptiness);
            __condition_variable_stream_emptiness.wait(lock, [] {
                return getStreamReader().isEmpty();
            });
        }

        void StreamThreadSafetyCheck::startChecking() {
            createDetachedReaders(1);
            createDetachedWriters(1);
            waitUntilStreamIsEmptied();
        }
    }
}
