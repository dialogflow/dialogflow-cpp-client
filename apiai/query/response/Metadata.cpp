#include "Metadata.h"

#include <memory>
#include <string>

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

