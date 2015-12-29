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
            try {
                return this->serialize(this->performConnection());
            } catch(...) {
                throw;
            }
        }
    protected:
        RequestSerialize(std::string URL): RequestConnection(URL) {}
        virtual T serialize(const std::string& response) = 0;
    };
}

#endif // REQUESTSERIALIZE

