#include <apiai/query/response/Result.h>

#include "indent_stream.h"

#include <memory>
#include <string>
#include <ostream>

using namespace std;
using namespace ai::query::response;

Result::Result(const std::string source,
               const std::string resolvedQuery,
               const std::shared_ptr<std::string> action,
               const std::shared_ptr<Fulfillment> fulfillment,
               const Metadata metadata,
               const std::vector<ai::query::response::Context> contexts):
    source(source), resolvedQuery(resolvedQuery), action(action), fulfillment(fulfillment), metadata(metadata), contexts(contexts)
{

}

Result::~Result() {

}

std::vector<Context> Result::getContexts() const
{
    return contexts;
}

Metadata Result::getMetadata() const
{
    return metadata;
}

std::shared_ptr<Fulfillment> Result::getFulfillment() const
{
    return fulfillment;
}

std::string Result::getSource() const
{
    return source;
}

std::string Result::getResolvedQuery() const
{
    return resolvedQuery;
}

std::shared_ptr<std::string> Result::getAction() const
{
    return action;
}

namespace ai {
    namespace query {
        namespace response {
            std::ostream& operator << (std::ostream& os, const Result& result) {

                os << "Result:" << std::endl;
                os << "    " << "source: " << result.source << std::endl;
                os << "    " << "resolvedQuey: " << result.resolvedQuery << std::endl;
                os << "    " << "action: ";

                if (result.action.get()) {
                    os << *result.action;
                } else {
                    os << "NULL";
                }

                os << std::endl;

                os << "fufillment: ";

                if (result.fulfillment.get()) {
                    ai::utils::indent_stream indent_stream(os);
                    indent_stream << *result.fulfillment.get();
                } else {
                    os << "NULL";
                }

                os << std::endl;

                os << "metadata: ";
                {
                    ai::utils::indent_stream indent_stream(os);
                    indent_stream << result.metadata;
                }

                os << "contexts: [" << endl;

                ai::utils::indent_stream indent_stream(os);
                for (auto context: result.contexts) {
                    indent_stream << "{" << endl;

                    ostream& qwe = indent_stream;
                    ai::utils::indent_stream indent_stream2(qwe);

                    indent_stream2 << context;
                    indent_stream << "}, " << endl;
                }

                os << "]";

                return os;
            }
        }
    }
}
