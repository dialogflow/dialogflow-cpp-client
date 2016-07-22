#include <apiai/exceptions/ResponseErrorException.h>

using namespace ai;

ResponseErrorException::ResponseErrorException(
        const std::string &errorType,
        const std::string &errorDetails,
        const int &code)
    : std::runtime_error(errorDetails), errorType(errorType), errorDetails(errorDetails), code(code)
{

}
