#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <future>
#include <sstream>

#include <apiai/Credentials.h>

#include "RequestSerialize.h"

namespace ai {
    template <typename T>
    class Request: protected RequestSerialize<T> {
    public:
        virtual T perform() {
            return RequestSerialize<T>::perform();
        }
    protected:
        Request(const Credentials &credentials): RequestSerialize<T>(std::string("https://api.api.ai/v1/query?v=20150910")), credentials(credentials)
        {
            this->authentificate(credentials);
        }
    private:
        Request(const Request&);
        Credentials credentials;
    };
}

#endif // REQUEST_H
