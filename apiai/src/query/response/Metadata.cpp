#include <apiai/query/response/Metadata.h>

#include <memory>
#include <string>
#include <ostream>

using namespace std;
using namespace ai::query::response;

Metadata::Metadata(shared_ptr<string> intentId,
                   shared_ptr<string> intentName):
    intentId(intentId), intentName(intentName)
{

}

Metadata::Metadata(): intentId(nullptr), intentName(nullptr) {

}

shared_ptr<string> Metadata::getIntentId() const
{
    return intentId;
}

shared_ptr<string> Metadata::getIntentName() const
{
    return intentName;
}

Metadata::~Metadata()
{

}

namespace ai {
    namespace query {
        namespace response {
            std::ostream& operator << (std::ostream& os, const Metadata& metadata) {
                os << "Metadata: " << endl;

                os << "    " << "intentId: ";

                if (metadata.intentId.get()) {
                    os << *metadata.intentId.get();
                } else {
                    os << "NULL";
                }

                os << endl;

                os << "    " << "intentName: ";

                if (metadata.intentName.get()) {
                    os << *metadata.intentName.get();
                } else {
                    os << "NULL";
                }

                os << endl;

                return os;
            }
        }
    }
}
