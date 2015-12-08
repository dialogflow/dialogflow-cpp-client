#ifndef REQUESTCONNECTION
#define REQUESTCONNECTION

#include <memory>
#include <string>
#include <map>

#define NON_COPYABLE_NOR_MOVABLE(T) \
      T(T const &) = delete; \
      void operator=(T const &t) = delete; \
      T(T &&) = delete;

namespace ai {
    class Credentials;

    namespace io {
        class StreamWriter;
    }

    class RequestConnection {

    protected:
        RequestConnection(std::string URL);

        std::string performConnection();
        void authentificate(const Credentials& credentials);

        virtual ~RequestConnection();

        class RequestConnectionImpl;
        std::unique_ptr<RequestConnectionImpl> impl;
    private:
        NON_COPYABLE_NOR_MOVABLE(RequestConnection)
    };
}

#endif // REQUESTCONNECTION

