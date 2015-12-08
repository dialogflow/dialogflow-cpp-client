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
    namespace io {
        class StreamWriter;
    }

    class RequestConnection {

    protected:
        RequestConnection(std::string URL);

        std::string performConnection();

        virtual ~RequestConnection();
    private:
        NON_COPYABLE_NOR_MOVABLE(RequestConnection)

        class RequestConnectionImpl;
        std::unique_ptr<RequestConnectionImpl> impl;
    };
}

#endif // REQUESTCONNECTION

