#include <apiai/query/response/Fulfillment.h>

#include <ostream>
#include <string>

using namespace std;
using namespace ai::query::response;

Fulfillment::Fulfillment(std::string speech): speech(speech)
{

}

std::string Fulfillment::getSpeech() const
{
    return speech;
}


Fulfillment::~Fulfillment() {}

namespace ai {
    namespace query {
        namespace response {
            std::ostream& operator << (std::ostream& os, const Fulfillment& fulfillment) {
                os << "Fulfillment:" << endl;
                os << "    " << "speech: " << fulfillment.speech;

                return os;
            }
        }
    }
}
