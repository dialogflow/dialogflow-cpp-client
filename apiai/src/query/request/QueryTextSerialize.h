#ifndef QUERYTEXTSERIALIZE_H
#define QUERYTEXTSERIALIZE_H

#include <iostream>
#include "cJSON.h"

#include "QueryTextVisitor.h"

namespace ai {
    namespace query {
        namespace request {
            class QueryTextSerialize: public QueryTextVisitor
            {
            private:
                cJSON *query_element;
            public:

                QueryTextSerialize();

                virtual void visit(const QueryOne& ref) override;
                virtual void visit(const QueryMultipleStrings& ref) override;
                virtual void visit(const QueryMultipleVariants& ref) override;

                cJSON *getQuery_element() const;
            };
        }
    }
}

#endif // QUERYTEXTSERIALIZE_H
