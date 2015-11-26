#include "Fulfillment.h"

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
