#include <apiai/exceptions/InvalidArgumentException.h>

using namespace ai;

InvalidArgumentException::InvalidArgumentException(const std::string& message): std::runtime_error(message) {}
