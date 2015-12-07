#ifndef SERVICE_H
#define SERVICE_H

#include "Credentials.h"

namespace ai {
    class Service
    {
    private:
        Credentials credentials;
    public:
        Service(Credentials credentials);
    };
}

#endif // SERVICE_H
