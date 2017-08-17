/**
 * Copyright 2017 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <string>
#include <sstream>
#include <thread>

#include <unistd.h>

#include <io/Stream.h>
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
            writer.sealed(true);

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

        static std::string pathToSounds("/io/tests/sounds/");

        ///
        /// Files for testing
        ///

        static std::string filename_sound1("sound1.wav");
        static std::string filename_sound2("sound2.wav");
        static std::string filename_speech_d("speech_d");

        void *StreamThreadSafetyCheck::readFile(void *arg) {
            std::ifstream fstream;
            ai::io::StreamWriter writer = getStreamWriter();

            std::string path(getcwd(NULL, 0));
            path.append(pathToSounds);
            path.append(filename_sound1);

            __mutex_print.lock();
            std::cout << "File to read: " << path << std::endl;
            __mutex_print.unlock();

            fstream.open(path.c_str(), std::ifstream::binary);

            fstream.seekg (0, fstream.end);
            std::streamsize length = fstream.tellg();
            fstream.seekg (0, fstream.beg);

            __mutex_print.lock();
            std::cout << length << " bytes total." << std::endl;
            __mutex_print.unlock();

            const std::streamsize sizeOfBuffer = 2048;
            char *buffer = new char[sizeOfBuffer];
            while (length > 0) {
                const std::streamsize read = (sizeOfBuffer > length) ? length : sizeOfBuffer;
                __mutex_print.lock();
                std::cout << read << " bytes are about to be read." << std::endl;
                __mutex_print.unlock();

                fstream.read(buffer, read);
                writer.write(buffer, read);
                writer.flush();

                length -= sizeOfBuffer;
            }
            writer.sealed(true);

            delete [] buffer;
            buffer = NULL;

            return NULL;
        }

        void *StreamThreadSafetyCheck::writeFile(void *arg) {
            std::unique_lock<std::mutex> lock(__mutex_stream_emptiness);

            std::ofstream fstream;
            ai::io::StreamReader reader = getStreamReader();

            std::string path(getcwd(NULL, 0));
            path.append(pathToSounds);
            path.append("/clone.wav");

            fstream.open(path.c_str(), std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

            __mutex_print.lock();
            std::cout << fstream.is_open() << std::endl;
            std::cout << fstream.good() << std::endl;
            __mutex_print.unlock();

            const std::streamsize sizeOfBuffer = 2048;
            char *buffer = new char[sizeOfBuffer];
            while (true) {
                const std::streamsize read = reader.read(buffer, sizeOfBuffer);
                fstream.write(buffer, read);
                fstream.flush();

                __mutex_print.lock();
                std::cout << read << " bytes are written." << std::endl;
                __mutex_print.unlock();

                if (reader.atEnd()) {
                    break;
                }
            }

            delete [] buffer;
            buffer = NULL;

            lock.unlock();
            __condition_variable_stream_emptiness.notify_one();

            return NULL;
        }

        void StreamThreadSafetyCheck::createDetachedThreads(void *(*startRoutine)(void *), unsigned int numberOfThreads) {
            //FIXME: remove using index, becouse it can be deleted before thread will be started
            for (unsigned int index = 0; index < numberOfThreads; ++index) {
                std::thread thread(startRoutine, (void *)&index);
                thread.detach();
            }
        }

        void StreamThreadSafetyCheck::createDetachedWriter() {
            createDetachedThreads(write, 1);
        }

        void StreamThreadSafetyCheck::createDetachedReader() {
            createDetachedThreads(read, 1);
        }

        void StreamThreadSafetyCheck::waitUntilStreamIsEmptied() {
            std::unique_lock<std::mutex> lock(__mutex_stream_emptiness);
            __condition_variable_stream_emptiness.wait(lock, [] {
                return getStreamReader().atEnd();
            });
        }

#ifndef USES_AUDIO_FILE_TO_CHECK_THREAD_SAFETY
    #define USES_AUDIO_FILE_TO_CHECK_THREAD_SAFETY 1
#endif

        void StreamThreadSafetyCheck::startChecking() {
        #ifndef USES_AUDIO_FILE_TO_CHECK_THREAD_SAFETY
            createDetachedReader();
            createDetachedWriter();
        #else
            createDetachedThreads(writeFile, 1);
            createDetachedThreads(readFile, 1);
        #endif
            waitUntilStreamIsEmptied();
        }
    }

#undef USES_AUDIO_FILE_TO_CHECK_THREAD_SAFETY
}
