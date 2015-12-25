#include <apiai/query/request/Parameters.h>
#include <apiai/exceptions/InvalidArgumentException.h>

using namespace std;
using namespace ai::query::request;

Parameters::Parameters(std::string sessionId,
                       bool resetContexts,
                       std::shared_ptr<std::string> timeZone,
                       std::vector<RequestContext> contexts,
                       std::vector<Entity> entities
                       ):
    sessionId(sessionId), resetContexts(resetContexts), timeZone(timeZone), contexts(contexts), entities(entities)
{
    if (sessionId.size() == 0) {
        throw InvalidArgumentException("SessionId connot be zero length.");
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

Parameters& Parameters::addContext(RequestContext context)
{
    this->contexts.push_back(context);
    return *this;
}

Parameters& Parameters::addEntity(Entity entity)
{
    this->entities.push_back(entity);
    return *this;
}

bool Parameters::getResetContexts() const
{
    return resetContexts;
}

std::string Parameters::getSessionId() const
{
    return sessionId;
}

std::shared_ptr<std::string> Parameters::getTimeZone() const
{
    return timeZone;
}

std::vector<RequestContext> Parameters::getContexts() const
{
    return contexts;
}

std::vector<Entity> Parameters::getEntities() const
{
    return entities;
}

