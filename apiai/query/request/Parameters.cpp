#include "Parameters.h"

using namespace std;
using namespace ai::query::request;

Parameters::Parameters(std::string sessionId,
                       bool resetContexts,
                       std::shared_ptr<std::string> timeZone,
                       std::vector<std::string> contexts,
                       std::vector<std::string> entities
                       ):
    sessionId(sessionId), resetContexts(resetContexts), timeZone(timeZone), contexts(contexts), entities(entities)
{
    if (sessionId.size() == 0) {
        throw invalid_argument("SessionId connot be zero length.");
    }
}

Parameters& Parameters::setResetContexts(bool resetContexts)
{
    this->resetContexts = resetContexts;
    return *this;
}

Parameters& Parameters::setTimeZone(std::shared_ptr<std::string> timeZone)
{
    this->timeZone = timeZone;
    return *this;
}

Parameters& Parameters::addContext(std::string context)
{
    this->contexts.push_back(context);
    return *this;
}

Parameters& Parameters::addEntity(std::string entity)
{
    this->entities.push_back(entity);
    return *this;
}

