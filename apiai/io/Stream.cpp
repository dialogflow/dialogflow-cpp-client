#include "Stream.h"

namespace ai {
    namespace io {

        ///
        /// Thread-safe methods
        ///

        bool Stream::isEmpty() {
            std::unique_lock<std::mutex> lock(this->mutex);
            return this->unsafe_is_empty();
        }

        bool Stream::isSealed() {
            std::unique_lock<std::mutex> lock(this->mutex);
            return this->unsafe_is_sealed();
        }

        void Stream::seal() {
            std::unique_lock<std::mutex> lock(this->mutex);
            this->unsafe_seal();
        }

        Stream &Stream::write(const char *source, std::streamsize count) {
            {
                std::unique_lock<std::mutex> lock(this->mutex);
                if (this->unsafe_is_sealed()) {
                    return *this;
                }

                this->unsafe_write(source, count);
                this->unsafe_flush();
            }
            this->condition_variable.notify_all();

            return *this;
        }

        std::streamsize Stream::read(char *target, std::streamsize count) {
            std::streamsize read = 0;
            {
                std::unique_lock<std::mutex> lock(this->mutex);
                if (this->unsafe_good()) {
                    if (this->unsafe_is_sealed() && this->unsafe_is_empty()) {
                        return read;
                    }

                    this->condition_variable.wait(lock, [this]{
                        return (this->unsafe_in_avail() > 0);
                    });

                    const std::streamsize in_avail = this->unsafe_in_avail();
                    if (in_avail > 0) {
                        read = std::min(in_avail, count);
                        this->unsafe_read(target, read);
                    }
                }
            }

            return read;
        }

        ///
        /// Thread-unsafe methods
        ///

        bool Stream::unsafe_is_empty() {
            return (this->unsafe_in_avail() == 0);
        }

        bool Stream::unsafe_is_sealed() const {
            return this->sealed;
        }

        void Stream::unsafe_seal() {
            if (!this->unsafe_is_sealed()) {
                this->sealed = true;
            }
        }

        bool Stream::unsafe_good() const {
            return this->stringstream.good();
        }

        std::streampos Stream::unsafe_tellg() {
            return this->stringstream.tellg();
        }

        std::streampos Stream::unsafe_tellp() {
            return this->stringstream.tellp();
        }

        std::streamsize Stream::unsafe_in_avail() {
            const std::streampos gpos = this->unsafe_tellg(); // input
            const std::streampos ppos = this->unsafe_tellp(); // output

            return (gpos < ppos) ? (ppos - gpos) : 0;
        }

        std::stringstream &Stream::unsafe_write(const char *source, std::streamsize count) {
            this->stringstream.write(source, count);

            return this->stringstream;
        }

        std::stringstream &Stream::unsafe_read(char *target, std::streamsize count) {
            this->stringstream.read(target, count);

            return this->stringstream;
        }

        void Stream::unsafe_flush() {
            this->stringstream.flush();
        }
    }
}
