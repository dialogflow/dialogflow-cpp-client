#ifndef REQUESTSERIALIZE
#define REQUESTSERIALIZE

#include "RequestConnection.h"

#include <apiai/exceptions/InvalidArgumentException.h>
#include <apiai/exceptions/JSONException.h>


namespace ai{
    template <typename T>
    class RequestSerialize: protected RequestConnection {
    public:
        virtual T perform() {
            return this->serialize(this->performConnection());
        }
    protected:
        RequestSerialize(std::string URL): RequestConnection(URL) {}
        virtual T serialize(const std::string& response) _GLIBCXX_THROW(InvalidArgumentException) = 0;
    };
}

#endif // REQUESTSERIALIZE

