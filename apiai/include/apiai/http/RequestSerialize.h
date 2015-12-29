#ifndef REQUESTSERIALIZE
#define REQUESTSERIALIZE

#include "RequestConnection.h"

#include <apiai/exceptions/InvalidArgumentException.h>
#include <apiai/exceptions/JSONException.h>

#include <iostream>

namespace ai{
    template <typename T>
    class RequestSerialize: public RequestConnection {
    public:
        virtual T perform() {
            try {
                auto resp = this->performConnection();
                return this->serialize(resp);
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

