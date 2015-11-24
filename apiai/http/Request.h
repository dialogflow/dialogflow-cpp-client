#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <future>
#include "../Credentials.h"


namespace ai {
class Request
{
private:
    Request(const Request&);
    Credentials credentials;

    class RequestImpl;
    std::unique_ptr<RequestImpl> impl;
protected:
    virtual void perform();

public:
    Request(Credentials credentials);

    std::future<int> async_perform();

    virtual ~Request();
};
}

#endif // REQUEST_H
