#include <apiai/exceptions/Exception.h>

using namespace ai;

Exception::Exception(const std::string& message): std::runtime_error(message) {}
