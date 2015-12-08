#ifndef REQUESTSERIALIZE
#define REQUESTSERIALIZE

#include "RequestConnection.h"

namespace ai{
    template <typename T>
    class RequestSerialize: protected RequestConnection {
    public:
        virtual T perform() {
            return this->serialize(this->performConnection());
        }
    protected:
        virtual T serialize(std::string) = 0;
    };
}

#endif // REQUESTSERIALIZE

