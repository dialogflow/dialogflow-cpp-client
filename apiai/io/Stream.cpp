#include "Stream.h"

namespace ai {
    namespace io {

        ///
        /// Thread-safe methods
        ///

        bool Stream::isAtEnd() {
            std::unique_lock<std::mutex> lock(this->mutex);
            return this->unsafeIsAtEnd();
        }

        bool Stream::isSealed() {
            std::unique_lock<std::mutex> lock(this->mutex);
            return this->unsafeIsSealed();
        }

        void Stream::seal() {
            std::unique_lock<std::mutex> lock(this->mutex);
            this->unsafeSeal();
        }

        Stream &Stream::write(const char *source, std::streamsize count) {
            {
                std::unique_lock<std::mutex> lock(this->mutex);
                if (this->unsafeIsSealed()) {
                    return *this;
                }

                this->unsafeWrite(source, count);
                this->unsafeFlush();
            }
            this->conditionVariable.notify_all();

            return *this;
        }

        std::streamsize Stream::read(char *target, std::streamsize count) {
            std::streamsize read = 0;
            {
                std::unique_lock<std::mutex> lock(this->mutex);
                if (this->unsafeGood()) {
                    if (this->unsafeIsAtEnd()) {
                        return read;
                    }

                    this->conditionVariable.wait(lock, [this]{
                        return (this->unsafeInAvail() > 0);
                    });

                    const std::streamsize inAvail = this->unsafeInAvail();
                    if (inAvail > 0) {
                        read = std::min(inAvail, count);
                        this->unsafeRead(target, read);
                    }
                }
            }

            return read;
        }

        ///
        /// Thread-unsafe methods
        ///

        bool Stream::unsafeIsAtEnd() {
            return (this->unsafeIsSealed()) && (this->unsafeInAvail() == 0);
        }

        bool Stream::unsafeIsSealed() const {
            return this->sealed;
        }

        void Stream::unsafeSeal() {
            if (!this->unsafeIsSealed()) {
                this->sealed = true;
            }
        }

        bool Stream::unsafeGood() const {
            return this->stringstream.good();
        }

        std::streampos Stream::unsafeTellg() {
            return this->stringstream.tellg();
        }

        std::streampos Stream::unsafeTellp() {
            return this->stringstream.tellp();
        }

        std::streamsize Stream::unsafeInAvail() {
            const std::streampos gpos = this->unsafeTellg(); // input
            const std::streampos ppos = this->unsafeTellp(); // output

            return (gpos < ppos) ? (ppos - gpos) : 0;
        }

        std::stringstream &Stream::unsafeWrite(const char *source, std::streamsize count) {
            this->stringstream.write(source, count);

            return this->stringstream;
        }

        std::stringstream &Stream::unsafeRead(char *target, std::streamsize count) {
            this->stringstream.read(target, count);

            return this->stringstream;
        }

        void Stream::unsafeFlush() {
            this->stringstream.flush();
        }
    }
}
