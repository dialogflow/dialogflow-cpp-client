#ifndef SERIALIZATION
#define SERIALIZATION

#include <string>

template <typename T>
class Serialization {
    virtual T serialize(std::string source) = 0;
};


#endif // SERIALIZATION
